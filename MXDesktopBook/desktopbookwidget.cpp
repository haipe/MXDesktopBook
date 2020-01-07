#include "desktopbookwidget.h"
#include "ui_desktopbookwidget.h"
#include <QMouseEvent>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDesktopWidget>
#include <QTimer>


DesktopBookWidget::DesktopBookWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DesktopBookWidget)
{
    ui->setupUi(this);

    qRegisterMetaType<ZhengNengLiangInfo>("ZhengNengLiangInfo");

    font.setPointSize(18);
    font.setBold(true);

    ui->label_text->setFont(font);
    ui->label_text->setWordWrap(true);

    font.setPointSize(14);
    font.setBold(true);
    ui->label_creator->setFont(font);
    ui->label_creator->setWordWrap(true);

    webrequest_lib = new QLibrary("MXWebRequest.dll");
    if (webrequest_lib->load())
    {
        mx_dll_function.mx_dll_init = (mxtoolkit::MX_DLL_FUNCTION_TYPE(mx_dll_init))webrequest_lib->resolve("mx_dll_init");
        mx_dll_function.mx_dll_uninit = (mxtoolkit::MX_DLL_FUNCTION_TYPE(mx_dll_uninit))webrequest_lib->resolve("mx_dll_uninit");
        mx_dll_function.mx_dll_all_export = (mxtoolkit::MX_DLL_FUNCTION_TYPE(mx_dll_all_export))webrequest_lib->resolve("mx_dll_all_export");
        mx_dll_function.mx_dll_get_interface = (mxtoolkit::MX_DLL_FUNCTION_TYPE(mx_dll_get_interface))webrequest_lib->resolve("mx_dll_get_interface");
    }

    if(mx_dll_function.mx_dll_init)
        mx_dll_function.mx_dll_init();

    mxtoolkit::mx_dll_export_info* all_export = nullptr;
    if(mx_dll_function.mx_dll_all_export)
    {
        mx_dll_function.mx_dll_all_export(&all_export);
    }

    loadNew();
}

DesktopBookWidget::~DesktopBookWidget()
{
    if(webrequest)
    {
        webrequest->Uninstall();
        webrequest = nullptr;
    }

    if(mx_dll_function.mx_dll_uninit)
    {
        mx_dll_function.mx_dll_uninit();
        mx_dll_function = {nullptr,nullptr,nullptr,nullptr};
    }

    if(webrequest_lib && webrequest_lib->isLoaded())
        webrequest_lib->unload();

    delete ui;
}

void DesktopBookWidget::init()
{
    connect(this,SIGNAL(onZhengNengLiang(const ZhengNengLiangInfo&)), this, SLOT(on_znl_come(const ZhengNengLiangInfo&)),Qt::QueuedConnection);

    QRect rc = QApplication::desktop()->availableGeometry();
    qDebug()<<"screen  width: "<<rc.width();
    qDebug()<<"screen height: "<<rc.height();

    this->setGeometry(0,rc.height() - this->size().height(),rc.width(),this->size().height());
    qDebug() << "geometry: " << this->geometry();
    show();
}

void DesktopBookWidget::loadNew()
{
    mxtoolkit::mx_export_interface_info iInfo = {"WebRequest","202001061800"};
    if(!webrequest && mx_dll_function.mx_dll_get_interface)
    {
        mx_dll_function.mx_dll_get_interface(&iInfo,(void**)&webrequest);

        if(webrequest)
            webrequest->Initialize(this);
    }

    if(webrequest)
    {
        mxwebrequest::Request rq;
        rq.request_type = mxwebrequest::REQUEST_TYPE_GET;
        rq.request_protocol = mxwebrequest::REQUEST_PROTOCOLTYPE_HTTPS;
        rq.respond_data_protocol = mxwebrequest::RESPOND_PROTOCOL_JSON;
        rq.request_host = (CHAR*)"https://v1.hitokoto.cn";

        load_request_id = webrequest->AsynRequest(&rq);
        qDebug() << "rquest ID:" << load_request_id;

        timeout_check_request_id = load_request_id;
        QTimer::singleShot(3000,this,SLOT(on_load_timeout()));
    }
}

void DesktopBookWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        b_mouse_pressed = true;
        position = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void DesktopBookWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    if(event->button()==Qt::LeftButton)
    {
        qDebug() << "leftbutton DBClick :" << load_request_id;
        if(load_request_id == 0)
            loadNew();
    }
    if(event->button()==Qt::RightButton)
    {
        close();
        if(webrequest)
        {
            webrequest->Uninstall();
        }

        if(mx_dll_function.mx_dll_uninit)
            mx_dll_function.mx_dll_uninit();

        emit onClose();
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

void DesktopBookWidget::OnCompleteRespond(mxtoolkit::uint32 nID, mxtoolkit::uint32 nCode,const char *pData, mxtoolkit::uint32 nSize)
{
    if(load_request_id == 0)
        return;

    qDebug() << "rquest ID:" << nID
             << ",Code:" << nCode
             << ",res:" << pData
             << ",resSize:" << nSize;

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(QString::fromUtf8((const char*)pData).toUtf8() , &jsonError));
    if(jsonError.error != QJsonParseError::NoError)
    {
        qDebug() << "OnCompleteRespond: " << jsonError.errorString();
        return;
    }

    QJsonObject rootObj = jsonDoc.object();
    if(rootObj.isEmpty())
        return;

    if(!rootObj.contains("id"))
        return;

    ZhengNengLiangInfo info;
    info.id = rootObj["id"].toInt();
    info.title = rootObj["hitokoto"].toString();
    info.type = rootObj["type"].toString();
    info.from = rootObj["from"].toString();
    info.creator = rootObj["creator"].toString();
    info.createDate = rootObj["created_at"].toString();

    load_request_id = 0;
    emit onZhengNengLiang(info);
}

void DesktopBookWidget::on_znl_come(const ZhengNengLiangInfo& info)
{
    color = QColor::fromHsl(rand() % 360, rand() % 256, rand() % 200);
    pe.setColor(QPalette::WindowText, color);
    ui->label_text->setPalette(pe);
    ui->label_creator->setPalette(pe);

    ui->label_text->setText(info.title);
    ui->label_creator->setText(info.creator);

    //5分钟更新一个
    QTimer::singleShot(5 * 60 * 1000,this,SLOT(on_need_load_new()));
}

void DesktopBookWidget::on_load_timeout()
{
    qDebug() << "DesktopBookWidget::on_load_timeout" << load_request_id << ": " << timeout_check_request_id;
    //超时了，重新请求
    if(load_request_id == timeout_check_request_id)
    {
        load_request_id = 0;
        loadNew();
    }
}

void DesktopBookWidget::on_need_load_new()
{
    qDebug() << "DesktopBookWidget::on_need_load_new" << load_request_id;
    loadNew();
}
