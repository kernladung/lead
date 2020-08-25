/*

MIT License

Copyright (c) 2017 Noah Andreas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/


#include "app.h"
#include "sensor.h"
#include "screenname.h"
#include <QDebug>
#include <QScreen>
#include <QFileSystemWatcher>
#include <QVariant>

#define SENSOR_WIDTH 5
#define SENSOR_HEIGHT 5
#define DEBUG_MODE_KEY "systemsettings/debug"

namespace Lead {


App::App(int &argc, char** argv) :
    QApplication(argc, argv),
    settings("lead", "lead"),
    watcher()
{   
    loadScreens();
    watchSettings();
}


App::~App()
{
    qDeleteAll(sensors);
    qDeleteAll(screenNames);
}


void
App::watchSettings()
{    
    watcher.addPath(settings.fileName());

    connect(&watcher, SIGNAL(fileChanged(QString)), this, SLOT(fileChanged(QString)));
}


void
App::fileChanged(QString fileName)
{
    qDebug() << "App::fileChanged() fileName: " << fileName;

    // this reloads the settings from the file
    settings.sync();

    // some editors dont update but delete/create the config file, in this 
    // case our watcher loses the file so we have to add it again
    watcher.addPath( fileName );

    // simply reload everything
    reloadScreens();
}


void
App::screenAdded(QScreen* screen)
{
    loadScreen(screen);
}


void
App::screenRemoved(QScreen* screen)
{
    // thats the easiest way
    reloadScreens();
}


void
App::reloadScreens()
{
    qDeleteAll(sensors);
    qDeleteAll(screenNames);
    sensors.clear();
    screenNames.clear();

    loadScreens();
}


void
App::loadScreens()
{
    // first load the debug mode flag
    this->debugMode = false;

    if (settings.contains (DEBUG_MODE_KEY))
    {
        this->debugMode = settings.value (DEBUG_MODE_KEY).toInt () > 0;
    }

    foreach (QScreen* screen, screens()) 
    {
        loadScreen(screen);
    }
}


void
App::loadScreen(QScreen* screen)
{
    qDebug() << "App::loadScreen() " << screen->name();

    QRect rec = screen->geometry();
    
    loadSensor(screen, "top", rec.x() + (rec.width() / 3), rec.y(), rec.width() / 3, SENSOR_WIDTH);
    loadSensor(screen, "right", rec.x() + rec.width() - SENSOR_WIDTH, rec.y() + (rec.height() / 3), SENSOR_WIDTH, rec.height() / 3);
    loadSensor(screen, "bottom", rec.x() + (rec.width() / 3), rec.y() + rec.height() - SENSOR_HEIGHT, rec.width() / 3, SENSOR_HEIGHT);
    loadSensor(screen, "left", 0, rec.x() + (rec.height() / 3), SENSOR_WIDTH, rec.height() / 3);
    loadSensor(screen, "topLeft", rec.x(), rec.y(), SENSOR_WIDTH, SENSOR_HEIGHT);
    loadSensor(screen, "topRight", rec.x() + rec.width() - SENSOR_WIDTH, rec.y(), SENSOR_WIDTH, SENSOR_HEIGHT);
    loadSensor(screen, "bottomRight", rec.x() + rec.width() - SENSOR_WIDTH, rec.y() + rec.height() - SENSOR_HEIGHT, SENSOR_WIDTH, SENSOR_HEIGHT);
    loadSensor(screen, "bottomLeft", rec.x(), rec.y() + rec.height() - SENSOR_HEIGHT, SENSOR_WIDTH, SENSOR_HEIGHT);

    loadScreenNameDisplay (screen);
}


void
App::loadSensor(QScreen* screen, QString name, int x, int y, int w, int h)
{
    QString sensorNameKey = screen->name() + "/" + name;

    if (settings.contains (sensorNameKey) == false)
    {
        return;
    }

    QString sensorName          = settings.value (sensorNameKey).toString ();
    QString sensorEnterAction   = sensorName + "/enterAction";
    QString sensorExitAction    = sensorName + "/exitAction";
    QString sensorEnterDelay    = sensorName + "/enterDelay";
    QString sensorExitDelay     = sensorName + "/exitDelay";
    int emptyCount              = 0;

    if (sensorName.isEmpty () == true)
    {
        return;
    }

    if (!settings.contains (sensorEnterAction))
    {
        emptyCount ++;
    }

    if (!settings.contains (sensorExitAction))
    {
        emptyCount ++;
    }

    if (emptyCount == 2)
    {
        // to not make this a breaking change, keep compatibility with old configurations
        sensors.append (new Sensor (x, y, w, h, sensorName, "", 0, 0, this->debugMode));
        return;
    }

    if (!settings.contains (sensorEnterDelay))
    {
        qDebug () << "App::loadSensor () sensor " << sensorName << " does not have delay; setting to 0";
        settings.setValue (sensorEnterDelay, QVariant (0));
    }

    if (!settings.contains (sensorExitDelay))
    {
        qDebug () << "App::loadSensor () sensor " << sensorName << " does not have exit delay; setting to 0";
        settings.setValue (sensorExitDelay, QVariant (0));
    }

    qDebug () << "App::loadSensor () loaded sensor " << sensorName << " on screen " + screen->name();
    sensors.append (
            new Sensor (
                x, y, w, h,
                settings.value (sensorEnterAction).toString (),
                settings.value (sensorExitAction).toString (),
                settings.value (sensorEnterDelay).toInt (),
                settings.value (sensorExitDelay).toInt (),
                this->debugMode
            )
    );
}

void
App::loadScreenNameDisplay(QScreen* screen)
{
    if (!this->debugMode)
    {
        return;
    }

    qDebug () << "App::loadScreenNameDisplay () loading widget for screen " << screen->name ();

    screenNames.append (new ScreenName (screen));
}


} // namespace
