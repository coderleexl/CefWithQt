#include "QtWithCef.h"
#include "qdebug.h"
#include "../include/views/cef_window.h"

QtWithCef::QtWithCef(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    CCefWebView* testView = new CCefWebView(nullptr);
    testView->SetUrl("https://www.baidu.com");
    testView->setObjectName("1");
    CCefWebView* testView2 = new CCefWebView(this);
    testView2->SetUrl("https://www.baidu.com");
    testView2->setObjectName("2");
    auto pa = palette();
    pa.setBrush(QPalette::Background, Qt::red);
    testView->setPalette(pa);
    pa.setBrush(QPalette::Background, Qt::black);
    testView2->setPalette(pa);
    testView->setAutoFillBackground(true);
    testView2->setAutoFillBackground(true);
    testView->show();
    ui.mainLayout->addWidget(testView);
    ui.mainLayout->addWidget(testView2);

    connect(ui.lineEdit, &QLineEdit::returnPressed, this, [=] {
        testView2->SetUrl("https://www.baidu.com");
        testView->SetUrl("https://www.baidu.com");
        });
}

QtWithCef::~QtWithCef()
{}
