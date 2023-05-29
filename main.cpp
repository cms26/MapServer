#include "mainwindow.h"
#include "iconloader.h"
#include <QApplication>
#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGuiApplication::setWindowIcon(QIcon(IconLoader::getInstance().getIcon(IconLoader::IconName::Globe)));
    QQuickStyle::setStyle("Material");
    MainWindow w;
    w.show();
    return a.exec();
}
