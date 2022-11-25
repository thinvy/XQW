#include "mainwindow.hpp"
#include "loginWin.hpp"
#include <QApplication>
#include <QObject>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    gst_init(&argc, &argv);
    QApplication a(argc, argv);
    LoginWin login_win;
    MainWindow main_win;
    QObject::connect(&login_win,SIGNAL(loginIn()),&main_win,SLOT(loginInShow()));
    login_win.show();
    return a.exec();
}
