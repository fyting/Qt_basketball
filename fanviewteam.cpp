#include "fanviewteam.h"
#include "ui_fanviewteam.h"
#include <QtSql>
#include <QDebug>
#include <QMessageBox>

extern QString teamname;

FanViewTeam::FanViewTeam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FanViewTeam)
{
    ui->setupUi(this);
    this->setFixedSize(310, 390);
    setWindowTitle(QString::fromLocal8Bit("查看球队信息"));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("D:\\VS+QT\\practice\\basketball\\basketball.db");

    if(!db.open())
    {
      qDebug() << db.lastError();
      qFatal("Failed to connect.");
    }
    qDebug("Connected!");

    QSqlQuery qry;
    qry.prepare( "SELECT * FROM teaminfortable" ); //打开一种操作
    qry.exec(); //开始执行操作
    QSqlRecord rec = qry.record();

    QString teamid, teamcompany, teammanager, teamcoach;
    for(int r = 0; qry.next(); ++r)
    {
        QString nowteam = qry.value(1).toString();
        if(nowteam == teamname)
        {
            teamid = qry.value(0).toString();
            teamcompany = qry.value(2).toString();
            teammanager = qry.value(3).toString();
            teamcoach = qry.value(4).toString();
            break ;
        }
    }

    ui->lineEdit_8->setText(teamid);
    ui->lineEdit_9->setText(teamname);
    ui->lineEdit_10->setText(teamcompany);
    ui->lineEdit_11->setText(teammanager);
    ui->lineEdit_12->setText(teamcoach);
}

FanViewTeam::~FanViewTeam()
{
    delete ui;
}
