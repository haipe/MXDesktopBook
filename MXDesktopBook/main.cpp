#include <QApplication>

#include "desktopbookwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DesktopBookWidget db;
    db.setWindowOpacity(1.0);
    db.setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    db.setAttribute(Qt::WA_TranslucentBackground);
    db.init();

    a.connect( &db, SIGNAL( onClose() ), &a, SLOT( quit() ) );
    return a.exec();
}
