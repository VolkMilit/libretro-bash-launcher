/*
    RetroArch Splash (or Splash) - writen special for libretro sh launcher.
    Copyright (C) 2018 Volk_Milit (aka Ja'Virr-Dar)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <QApplication>
//#include <QCommandLineParser>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QDesktopWidget>
#include <QFont>
#include <QSettings>
#include <QDir>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QVariant>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(true);

    QVariant pixsize = 10;
    QString p_gtkrc = QDir::home().path() + "/.gtkrc-2.0";
    QFile fgtkrc(p_gtkrc);
    if (fgtkrc.exists())
    {
        QSettings gtkrc(p_gtkrc, QSettings::IniFormat);
        QString fname = gtkrc.value("gtk-font-name").toString();
        QStringList tmp = fname.split(" ");
        pixsize = tmp.at(tmp.size()-1);
    }

    QDialog widget(0, Qt::Dialog | Qt::FramelessWindowHint | Qt::Popup);

    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *label = new QLabel;
    QFont font;
    font.setPixelSize(pixsize.toInt() * 2);
    label->setFont(font);
    label->setText("Loading...");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    widget.setMinimumWidth(app.desktop()->geometry().width());
    widget.setMinimumHeight(app.desktop()->geometry().height());
    widget.setLayout(layout);

    widget.setStyleSheet("QWidget{background: black;} QLabel{color: white;}");

    widget.show();

    return app.exec();
}
