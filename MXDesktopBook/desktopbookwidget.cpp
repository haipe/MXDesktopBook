#include "desktopbookwidget.h"
#include "ui_desktopbookwidget.h"
#include <QMouseEvent>
#include <QDebug>


DesktopBookWidget::DesktopBookWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DesktopBookWidget)
{
    ui->setupUi(this);

    font.setPointSize(30);
    font.setBold(true);

    ui->label_text->setFont(font);
    ui->label_text->setWordWrap(true);

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

    mxtoolkit::mx_export_interface_info iInfo = {"WebRequest","202001061800"};
    if(mx_dll_function.mx_dll_get_interface)
    {
        mx_dll_function.mx_dll_get_interface(&iInfo,(void**)&webrequest);
    }

    if(webrequest)
    {
        webrequest->Initialize(this);

        mxwebrequest::Request rq;
        rq.request_type = mxwebrequest::REQUEST_TYPE_GET;
        rq.request_protocol = mxwebrequest::REQUEST_PROTOCOLTYPE_HTTPS;
        rq.respond_data_protocol = mxwebrequest::RESPOND_PROTOCOL_JSON;
        rq.request_host = (CHAR*)"https://v1.hitokoto.cn/";

       qDebug() << "rquest ID:" << webrequest->AsynRequest(&rq);
    }

    showText();
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

void DesktopBookWidget::OnCompleteRespond(mxtoolkit::uint32 nID, mxtoolkit::uint32 nCode, char *pData, mxtoolkit::uint32 nSize)
{
    qDebug() << "rquest ID:" << nID
             << ",Code:" << nCode
             << ",res:" << pData
             << ",resSize:" << nSize;
}

void DesktopBookWidget::showText()
{
    color = QColor::fromHsl(rand() % 360, rand() % 256, rand() % 200);
    pe.setColor(QPalette::WindowText, color);
    ui->label_text->setPalette(pe);
    QString sql = QStringLiteral("大苏打大苏打撒旦 ");

    ui->label_text->setText(sql);
}
