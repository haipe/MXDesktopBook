#ifndef DESKTOPBOOKWIDGET_H
#define DESKTOPBOOKWIDGET_H

#include <QWidget>
#include <QLibrary>
#include "IWebRequest.h"
#include "MXDllExportDefine.h"


namespace Ui {
class DesktopBookWidget;
}

class DesktopBookWidget
        : public QWidget
        , public mxwebrequest::IRespondNotify
{
    Q_OBJECT

public:
    explicit DesktopBookWidget(QWidget *parent = nullptr);
    virtual ~DesktopBookWidget() override;

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

    virtual void OnHeaderRespond(uint32 nID,char *pData,uint32 nSize) override{};
    virtual void OnDataRespond(uint32 nID,char *pData,uint32 nSize) override{};
    virtual void OnCompleteRespond(uint32 nID,uint32 nCode,char *pData,uint32 nSize) override;
private slots:
    void showText();

private:
    Ui::DesktopBookWidget *ui;

    QPoint position;
    bool b_mouse_pressed = false;

    QPalette pe;
    QFont font;
    QColor color;

    QLibrary* webrequest_lib;
    mxtoolkit::mx_dll_export mx_dll_function;

    mxwebrequest::IWebRequest* webrequest = nullptr;
};

#endif // DESKTOPBOOKWIDGET_H
