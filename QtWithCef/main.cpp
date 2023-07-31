#include "QtWithCef.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_EnableHighDpiScaling);
    CCefEngine::GetInstance()->InitEngine();

    QtWithCef w;
    w.show();
    int ret = a.exec();

    return ret;
}
