#include "loginWin.hpp"
#include "ui_loginWin.h"

#include <QMessageBox>
#include <QPushButton>
#include <QString>

LoginWin::LoginWin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWin)
{
    ui->setupUi(this);
    connect(ui->user_login,SIGNAL(clicked()),this,SLOT(login()));
}

LoginWin::~LoginWin()
{
    delete ui;
}

void LoginWin::login(){
   QString user=ui->user_number->text();
   QString password=ui->user_password->text();
   //if(user =="root"&&password=="root"){
   if(1){
       QMessageBox::information(this,"OK","Right Input");
       this->close();
       emit(loginIn());
   }else{
        QMessageBox::information(this,"Error","Wrong Input");
   }
}
