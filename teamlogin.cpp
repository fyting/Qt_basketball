#include "teamlogin.h"
#include "ui_teamlogin.h"
#include "teamoper.h"
#include "teamregister.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSql>

TeamLogin::TeamLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeamLogin)
{
    ui->setupUi(this);
    this->setFixedSize(700, 433);
    setWindowTitle(QString::fromLocal8Bit("我是球队!-球队登录"));
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

TeamLogin::~TeamLogin()
{
    delete ui;
}

void TeamLogin::on_pushButton_clicked() //球队退出
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromLocal8Bit("篮球比赛管理系统"), QString::fromLocal8Bit("确定退出?"), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
        exit(0);
}

void TeamLogin::on_pushButton_2_clicked() //球队返回主菜单
{
    this->close();
}

void TeamLogin::on_pushButton_3_clicked() //球队登录
{
    int flag = 0;

    QString num = ui->lineEdit->text();
    QString pass = ui->lineEdit_2->text();

    QSqlQuery qry;
    qry.prepare( "SELECT * FROM teamtable" ); //打开一种操作
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
        TeamOper team_oper;
        team_oper.exec();
        this->exec();
    }
    else
    {
       QMessageBox::warning(this, QString::fromLocal8Bit("球队登录"), QString::fromLocal8Bit("账号或密码错误"), QMessageBox::Yes); //警告对话框
       ui->lineEdit->clear(); //清除用户名
       ui->lineEdit_2->clear(); //清除密码
       ui->lineEdit->setFocus(); //鼠标回到用户名栏
    }
}

void TeamLogin::on_pushButton_4_clicked()
{
    TeamRegister teamres;
    teamres.exec();
}
