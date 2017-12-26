#include "fanlogin.h"
#include "ui_fanlogin.h"
#include "fanoper.h"
#include "fanregister.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSql>

fanlogin::fanlogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fanlogin)
{
    ui->setupUi(this);
    this->setFixedSize(700, 433);
    setWindowTitle(QString::fromLocal8Bit("我是球迷!-球迷登录"));
    ui->lineEdit->setFocus(); //鼠标回到用户名栏
    ui->lineEdit_2->setEchoMode(QLineEdit::Password); //输入密码时显示*

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("D:\\VS+QT\\practice\\basketball\\basketball.db");

    if(!db.open())
    {
      qDebug() << db.lastError();
      qFatal("Failed to connect.");
    }
    qDebug("Connected!");
}

fanlogin::~fanlogin()
{
    delete ui;
}

void fanlogin::on_pushButton_clicked() //球迷退出
{
//    QMessageBox::information(this,QString::fromLocal8Bit("篮球比赛管理系统"), QString::fromLocal8Bit("确定退出?"),QMessageBox::Yes);
//    exit(0);

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromLocal8Bit("篮球比赛管理系统"), QString::fromLocal8Bit("确定退出?"), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
        exit(0);
}

void fanlogin::on_pushButton_2_clicked() //球迷返回主菜单
{
    this->close();
}

void fanlogin::on_pushButton_3_clicked() //球迷登录
{
    int flag = 0;

    QString num = ui->lineEdit->text();
    QString pass = ui->lineEdit_2->text();

    QSqlQuery qry;
    qry.prepare( "SELECT * FROM fantable" ); //打开一种操作
    qry.exec(); //开始执行操作
    QSqlRecord rec = qry.record();

    for(int r = 0; qry.next(); ++r)
    {
        QString nownum = qry.value(0).toString();
        QString nowpass = qry.value(1).toString();
        if(nownum == num && nowpass == pass)
            flag = 1;
    }

    if(flag)
    {
        this->close();
        FanOper fan_oper;
        fan_oper.exec();
        this->exec();
    }
    else
    {
       QMessageBox::warning(this, QString::fromLocal8Bit("球迷登录"), QString::fromLocal8Bit("账号或密码错误"), QMessageBox::Yes); //警告对话框
       ui->lineEdit->clear(); //清除用户名
       ui->lineEdit_2->clear(); //清除密码
       ui->lineEdit->setFocus(); //鼠标回到用户名栏
    }
}

void fanlogin::on_pushButton_4_clicked() //球迷注册
{
    FanRegister fanres;
    fanres.exec();
}
