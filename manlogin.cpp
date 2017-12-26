#include "manlogin.h"
#include "ui_manlogin.h"
#include "manoper.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSql>

ManLogin::ManLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManLogin)
{
    ui->setupUi(this);
    this->setFixedSize(700, 433);
    setWindowTitle(QString::fromLocal8Bit("我是管理员!-管理员登录"));
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

ManLogin::~ManLogin()
{
    delete ui;
}

void ManLogin::on_pushButton_clicked() //管理员退出
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromLocal8Bit("篮球比赛管理系统"), QString::fromLocal8Bit("确定退出?"), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
        exit(0);
}

void ManLogin::on_pushButton_2_clicked() //管理员返回主菜单
{
    this->close();
}

void ManLogin::on_pushButton_3_clicked() //管理员登录
{
    int flag = 0;

    QString num = ui->lineEdit->text();
    QString pass = ui->lineEdit_2->text();

    QSqlQuery qry;
    qry.prepare( "SELECT * FROM mantable" ); //打开一种操作
    qry.exec(); //开始执行操作
    QSqlRecord rec = qry.record();

    for(int r = 0; qry.next(); ++r)
    {
        QString nownum = qry.value(0).toString();
        QString nowpass = qry.value(1).toString();
        if(nownum == num && nowpass == pass)
            flag = 1;
    }

    if((ui->lineEdit->text() == QString::fromLocal8Bit("qt") && ui->lineEdit_2->text() == QString::fromLocal8Bit("123")) || flag == 1)
    {
        this->close();
        ManOper man_oper;
        man_oper.exec();
        this->exec();
    }
    else
    {
       QMessageBox::warning(this, QString::fromLocal8Bit("管理员登录"), QString::fromLocal8Bit("账号或密码错误!\n注册管理员账号请联系管理员"), QMessageBox::Yes); //警告对话框
       ui->lineEdit->clear(); //清除用户名
       ui->lineEdit_2->clear(); //清除密码
       ui->lineEdit->setFocus(); //鼠标回到用户名栏
    }
}
