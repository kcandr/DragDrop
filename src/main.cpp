#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(drag);

    QApplication a(argc, argv);
    MainWindow window;
    window.openImage();
    window.show();
    
    return a.exec();
}
