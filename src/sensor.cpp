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


#include "sensor.h"
#include <QEvent>
#include <QDebug>
#include <QProcess>


namespace Lead {


Sensor::Sensor(int x, int y, int w, int h, QString enterAction, QString exitAction, int enterInterval, int exitInterval, bool debugMode):
    QWidget(),
    enterAction(enterAction),
    exitAction(exitAction),
    enterInterval(enterInterval),
    exitInterval(exitInterval),
    debugMode(debugMode)
{
    qDebug()
        << "lead::Sensor() " << x << "," << y << "," << w << "," << h
        << " : enterAction=" << enterAction
        << " : exitAction=" << exitAction
        << " : enterInterval=" << enterInterval
        << " : exitInterval=" << exitInterval;

    this->canTriggerExit = false;

    this->enterTimer = new QTimer(this);
    this->enterTimer->setSingleShot(true);
    this->enterTimer->setInterval(enterInterval);

    this->exitTimer = new QTimer (this);
    this->exitTimer->setSingleShot (true);
    this->exitTimer->setInterval (exitInterval);

    connect(this->enterTimer, SIGNAL(timeout()), this, SLOT(activateEnter()));
    connect(this->exitTimer, SIGNAL(timeout()), this, SLOT(activateExit()));

    if (this->debugMode)
    {
        setStyleSheet ("background-color: red");
    }
    else
    {
        setAttribute(Qt::WA_TranslucentBackground, true);
    }

    setGeometry(x, y, w, h);
    setWindowFlags(windowFlags() | Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );

    show();
}


Sensor::~Sensor()
{
    delete this->enterTimer;
    delete this->exitTimer;
}


void
Sensor::enterEvent(QEvent * event)
{
    qDebug()
        << "lead::Sensor::enterEvent() "<< this->x() << ":" << this->y()
        << " enterInterval: " << this->enterTimer
        << " exitInterval: " << this->exitTimer;

    this->enterTimer->start();
    this->exitTimer->start();

    if (this->debugMode)
        setStyleSheet ("background-color: yellow");
}


void
Sensor::leaveEvent(QEvent * event)
{
    qDebug()
            << "lead::Sensor::leaveEvent() "<< this->x() << ":" << this->y()
            << " enterInterval: " << this->enterTimer
            << " exitInterval: " << this->exitTimer;

    if (this->canTriggerExit)
    {
        QProcess::startDetached(exitAction);
    }

    if (this->debugMode)
        setStyleSheet ("background-color: red");

    this->enterTimer->stop();
    this->exitTimer->stop();
    this->canTriggerExit = false;
}


void
Sensor::activateEnter()
{
    qDebug() << "lead::Sensor::activateEnter() " << this->x() << ":" << this->y() << " action: " << this->enterAction;

    if (this->debugMode)
        setStyleSheet ("background-color: green");

    QProcess::startDetached(enterAction);
}

void Sensor::activateExit()
{
    qDebug () << "lead::Sensor::activateExit() " << this->x() << ":" << this->y() << " action: " << this->exitAction << " can run now";

    this->canTriggerExit = true;
}


} // namespace
