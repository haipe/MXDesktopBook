#ifndef DESKTOPBOOKWIDGET_H
#define DESKTOPBOOKWIDGET_H

#include "_qt_include.h"

namespace Ui {
class DesktopBookWidget;
}

class DesktopBookWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DesktopBookWidget(QWidget *parent = nullptr);
    virtual ~DesktopBookWidget() override;

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void showText();

private:
    Ui::DesktopBookWidget *ui;

    QPoint position;
    bool b_mouse_pressed = false;

    QPalette pe;
    QFont font;
    QColor color;
};

#endif // DESKTOPBOOKWIDGET_H
