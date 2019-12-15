#include "mainwindow.h"

#include <QApplication>

#include "desktopbookwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    DesktopBookWidget db;
    db.setWindowOpacity(1.0);
    db.setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    db.setAttribute(Qt::WA_TranslucentBackground);
    db.show();

    return a.exec();
}
