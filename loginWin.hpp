#ifndef LOGINWIN_HPP
#define LOGINWIN_HPP

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class LoginWin;
}
QT_END_NAMESPACE

class LoginWin : public QWidget
{
    Q_OBJECT

public:
    LoginWin(QWidget *parent = nullptr);
    ~LoginWin();

signals:
    void loginIn();

private slots:
    void login();

private:
    Ui::LoginWin *ui;
};
#endif // LOGINWIN_HPP
