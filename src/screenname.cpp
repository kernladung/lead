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


#include "screenname.h"
#include <QEvent>
#include <QDebug>
#include <QProcess>
#include <QLabel>
#include <QHBoxLayout>

#define SCREENNAME_WIDTH 150
#define SCREENNAME_HEIGHT 45

namespace Lead {
    ScreenName::ScreenName(QScreen* screen):
            QWidget()
    {
        qDebug()
                << "lead::ScreenName() " << screen->name ();
        QRect rec = screen->geometry();

        setGeometry(rec.x(), rec.y(), SCREENNAME_WIDTH, SCREENNAME_HEIGHT);
        setAttribute(Qt::WA_TranslucentBackground, true);
        setWindowFlags(windowFlags() | Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );

        // create the text widget and put it in the widget
        QHBoxLayout *layout = new QHBoxLayout ();
        QLabel* label = new QLabel ();
        label->setText (screen->name ());
        layout->addWidget (label);

        setLayout (layout);

        show();
    }
} // namespace
