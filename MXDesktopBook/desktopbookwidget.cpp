#include "desktopbookwidget.h"
#include "ui_desktopbookwidget.h"

DesktopBookWidget::DesktopBookWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DesktopBookWidget)
{
    ui->setupUi(this);

    font.setPointSize(30);
    font.setBold(true);

    ui->label_text->setFont(font);
    ui->label_text->setWordWrap(true);

    showText();
}

DesktopBookWidget::~DesktopBookWidget()
{
    delete ui;
}

void DesktopBookWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        b_mouse_pressed = true;
        position = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    else if (event->button() == Qt::RightButton)
    {
        close();
    }
}

void DesktopBookWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (b_mouse_pressed)
    {
        move(event->globalPos() - position);
        event->accept();
    }
}

void DesktopBookWidget::showText()
{
    color = QColor::fromHsl(rand() % 360, rand() % 256, rand() % 200);
    pe.setColor(QPalette::WindowText, color);
    ui->label_text->setPalette(pe);
    QString sql = QStringLiteral("大苏打大苏打撒旦 ");

    ui->label_text->setText(sql);
}
