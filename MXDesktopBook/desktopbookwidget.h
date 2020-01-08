#ifndef DESKTOPBOOKWIDGET_H
#define DESKTOPBOOKWIDGET_H

#include <QWidget>
#include <QLibrary>
#include "IWebRequest.h"
#include "MXDllExportDefine.h"


struct ZhengNengLiangInfo
{
    ZhengNengLiangInfo()
    {
    }

    unsigned int id;
    QString title;
    QString type;
    QString from;
    QString creator;
    QString createDate;
};

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

    void init();

signals:
    void onZhengNengLiang(const ZhengNengLiangInfo&);
    void onClose();

protected:
    void loadNew();

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

    virtual void OnCompleteRespond(uint32 nID,uint32 nCode, const char *pData,uint32 nSize) override;

protected slots:
    void on_znl_come(const ZhengNengLiangInfo&);
    void on_load_timeout();
    void on_need_load_new();


private:
    Ui::DesktopBookWidget *ui;

    QPoint position;
    bool b_mouse_pressed = false;

    QPalette pe;
    QFont font;
    QColor color;

    QLibrary* webrequest_lib;
    mxtoolkit::MXDllObject mx_dll_object;

    mxwebrequest::IWebRequest* webrequest = nullptr;

    unsigned int timeout_check_request_id = 0;
    unsigned int load_request_id = 0;
};

#endif // DESKTOPBOOKWIDGET_H
