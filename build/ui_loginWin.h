/********************************************************************************
** Form generated from reading UI file 'loginWin.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIN_H
#define UI_LOGINWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWin
{
public:
    QLineEdit *user_password;
    QPushButton *user_login;
    QLineEdit *user_number;
    QLabel *name;

    void setupUi(QWidget *LoginWin)
    {
        if (LoginWin->objectName().isEmpty())
            LoginWin->setObjectName(QStringLiteral("LoginWin"));
        LoginWin->resize(557, 371);
        user_password = new QLineEdit(LoginWin);
        user_password->setObjectName(QStringLiteral("user_password"));
        user_password->setGeometry(QRect(120, 210, 301, 41));
        user_login = new QPushButton(LoginWin);
        user_login->setObjectName(QStringLiteral("user_login"));
        user_login->setGeometry(QRect(210, 270, 121, 51));
        user_number = new QLineEdit(LoginWin);
        user_number->setObjectName(QStringLiteral("user_number"));
        user_number->setGeometry(QRect(120, 140, 301, 41));
        name = new QLabel(LoginWin);
        name->setObjectName(QStringLiteral("name"));
        name->setGeometry(QRect(20, 40, 511, 81));
        QFont font;
        font.setPointSize(17);
        name->setFont(font);

        retranslateUi(LoginWin);

        QMetaObject::connectSlotsByName(LoginWin);
    } // setupUi

    void retranslateUi(QWidget *LoginWin)
    {
        LoginWin->setWindowTitle(QApplication::translate("LoginWin", "\347\231\273\351\231\206\347\225\214\351\235\242", Q_NULLPTR));
        user_password->setText(QString());
        user_password->setPlaceholderText(QApplication::translate("LoginWin", "Password", Q_NULLPTR));
        user_login->setText(QApplication::translate("LoginWin", "Login", Q_NULLPTR));
        user_number->setPlaceholderText(QApplication::translate("LoginWin", "Account", Q_NULLPTR));
        name->setText(QApplication::translate("LoginWin", "Panoramic intelligent security system - edge end", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginWin: public Ui_LoginWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIN_H
