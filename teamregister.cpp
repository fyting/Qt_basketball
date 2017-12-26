#include "teamregister.h"
#include "ui_teamregister.h"
#include <QtSql>
#include <QDebug>
#include <QMessageBox>

TeamRegister::TeamRegister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeamRegister)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();
    ui->lineEdit_2->setEchoMode(QLineEdit::Password); //输入密码时显示*
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);

    this->setFixedSize(500, 309);
    setWindowTitle(QString::fromLocal8Bit("球队注册"));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("D:\\VS+QT\\practice\\basketball\\basketball.db");

    if(!db.open())
    {
      qDebug() << db.lastError();
      qFatal("Failed to connect.");
    }
    qDebug("Connected!");
}

TeamRegister::~TeamRegister()
{
    delete ui;
}

void TeamRegister::on_pushButton_2_clicked() //球队注册返回
{
    this->close();
}

void TeamRegister::on_pushButton_clicked()
{
    QString num = ui->lineEdit->text();
    QString pass1 = ui->lineEdit_2->text();
    QString pass2 = ui->lineEdit_3->text();

    if(num == "" || pass1 == "" || pass2 == "")
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("球队注册"), QString::fromLocal8Bit("不能为空!"), QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit->setFocus();
        return ;
    }

    if(pass1 != pass2)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("球队注册"), QString::fromLocal8Bit("两次输入的密码不一致!"), QMessageBox::Yes);
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_2->setFocus();
        return ;
    }

    QSqlQuery qry;
    qry.prepare( "SELECT * FROM teamtable" ); //打开一种操作
    qry.exec(); //开始执行操作
    QSqlRecord rec = qry.record();

    for(int r = 0; qry.next(); ++r)
    {
        QString nowstring = qry.value(0).toString();
        if(nowstring == num)
        {
            QMessageBox::warning(this, QString::fromLocal8Bit("球队注册"), QString::fromLocal8Bit("该账号已被注册!"), QMessageBox::Yes);
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit->setFocus();
            return ;
        }
    }

    qry.prepare("create table if not exists teamtable(number char(30) unique primary key, password char(30)");
    qry.exec(QString("insert into teamtable(number, password) values('%1', '%2')").arg(num).arg(pass1));

    QMessageBox::information(this, QString::fromLocal8Bit("球队注册"), QString::fromLocal8Bit("注册成功!"), QMessageBox::Yes);

    this->close();
}
