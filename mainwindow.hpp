#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include <opencv2/opencv.hpp>
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    cv::VideoCapture cap;
    QTimer * timer;
    void display();

signals:
    void videoLost();

public slots:
    void  loginInShow();
    void  reOpenCam();
    void  videoErrorShow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HPP
