#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWithCef.h"

#include "CCefEngine.h"
#include "../cef_binary/tests/cefsimple/simple_handler.h"
#include "../cef_binary/tests/cefsimple/simple_app.h"

class QtWithCef : public QMainWindow
{
    Q_OBJECT

public:
    QtWithCef(QWidget *parent = nullptr);
    ~QtWithCef();
private:

    Ui::QtWithCefClass ui;
};
