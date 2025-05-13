#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.setWindowOpacity(0.5);
    w.show();
    return a.exec();
}
/*#include "mainwindow.h"
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 指定使用 xcb 平台插件
    a.setPlatformName("xcb");

    MainWindow w;
    w.setWindowOpacity(0.5);
    w.show();

    return a.exec();
}*/
