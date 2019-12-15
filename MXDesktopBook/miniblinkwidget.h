#ifndef MINIBLINKWIDGET_H
#define MINIBLINKWIDGET_H

#include "_qt_include.h"
#include "wke.h"


class MiniBlinkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MiniBlinkWidget(QWidget *parent = nullptr);

    virtual ~MiniBlinkWidget() override;

    static void wkeInit();
    static void wkeFinal();
signals:

public slots:

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

protected:
    wkeWebView web_view;
};

#endif // MINIBLINKWIDGET_H
