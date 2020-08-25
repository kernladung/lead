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


#pragma once


#include "sensor.h"
#include "screenname.h"
#include <QApplication>
#include <QList>
#include <QSettings>
#include <QScreen>
#include <QFileSystemWatcher>


namespace Lead {


class App : public QApplication
{
    Q_OBJECT

public:
    explicit App(int &argc, char** argv);
    ~App();

private:
    QSettings settings;
    QFileSystemWatcher watcher;
    QList<Sensor*> sensors;
    QList<ScreenName*> screenNames;
    bool debugMode;

    void screenAdded(QScreen* screen);
    void screenRemoved(QScreen* screen);
    void watchSettings();
    void loadScreens();
    void loadScreen(QScreen* screen);    
    void loadSensor(QScreen* screen, QString name, int x, int y, int w, int h);
    void loadScreenNameDisplay(QScreen* screen);
    void reloadScreens();
    
public slots:
    void fileChanged(QString fileName);

};


} // namespace