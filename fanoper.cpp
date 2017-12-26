#include "fanoper.h"
#include "ui_fanoper.h"
#include "fanviewteam.h"
#include "fanviewplayer.h"
#include "buy.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSql>
#include <cstring>
#include <iostream>
using namespace std;
#define LL long long

QString teamname;
QString teamid;
QString money;
QString buy_team1, buy_team2, buy_time, buy_price, buy_hold;

FanOper::FanOper(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FanOper)
{
    ui->setupUi(this);
    this->setFixedSize(700, 433);
    setWindowTitle(QString::fromLocal8Bit("我是球迷!"));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("D:\\VS+QT\\practice\\basketball\\basketball.db");

    if(!db.open())
    {
      qDebug() << db.lastError();
      qFatal("Failed to connect.");
    }
    qDebug("Connected!");

    scoremodel = new QSqlTableModel(this);
    scoremodel->setTable("scoretable");
    scoremodel->select();
    ui->tableView_5->horizontalHeader()->hide();
    ui->tableView_5->setModel(scoremodel);
    ui->tableView_5->setColumnWidth(0,80);
    ui->tableView_5->setColumnWidth(1,60);
    ui->tableView_5->setColumnWidth(2,80);
    ui->tableView_5->setColumnWidth(3,60);
    ui->tableView_5->setColumnWidth(4,128);
    ui->tableView_5->setColumnWidth(5,160);

    ticketmodel = new QSqlTableModel(this);
    ticketmodel->setTable("ticket");
    ticketmodel->select();
    ui->tableView_6->horizontalHeader()->hide();
    ui->tableView_6->setModel(ticketmodel);
    ui->tableView_6->setColumnWidth(0,70);
    ui->tableView_6->setColumnWidth(1,70);
    ui->tableView_6->setColumnWidth(2,70);
    ui->tableView_6->setColumnWidth(3,72);
    ui->tableView_6->setColumnWidth(4,137);
    ui->tableView_6->setColumnWidth(5,50);
    ui->tableView_6->setColumnWidth(6,50);
    ui->tableView_6->setColumnWidth(7,50);

    QSqlQuery qry;
    qry.prepare( "SELECT * FROM ticket" ); //打开一种操作
    qry.exec(); //开始执行操作
    QSqlRecord rec = qry.record();

    QString judge = QString::fromLocal8Bit("在售");
    for(int r = 0; qry.next(); ++r)
    {
        QString nowstatus = qry.value(6).toString();
        QString nowhold = qry.value(7).toString();
        if(nowstatus != judge || nowhold == "0")
        {qDebug() << nowstatus << nowhold;
            ui->tableView_6->setRowHidden(r,1);
        }
    }
}

FanOper::~FanOper()
{
    delete ui;
}

void FanOper::on_pushButton_clicked() //比赛结果的退出
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromLocal8Bit("篮球比赛管理系统"), QString::fromLocal8Bit("确定退出?"), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
        exit(0);
}

void FanOper::on_pushButton_2_clicked() //比赛结果的返回主菜单
{
    this->close();
}

void FanOper::on_pushButton_4_clicked() //查看该球队信息
{
    QSqlQuery qry;
    qry.prepare( "SELECT * FROM teaminfortable" ); //打开一种操作
    qry.exec(); //开始执行操作
    QSqlRecord rec = qry.record();

    int find = 0;
    for(int r = 0; qry.next(); ++r)
    {
        QString nowteam = qry.value(1).toString();
        if(nowteam == teamname)
        {
            find = 1;
            break ;
        }
    }
    if(teamname == "" || find == 0)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("查看球队信息"), QString::fromLocal8Bit("请在表中选择一支球队进行查看!"), QMessageBox::Yes);
        return ;
    }
    FanViewTeam fanviewt;
    fanviewt.exec();
}

void FanOper::on_pushButton_3_clicked() //查看该队球员信息
{
    QSqlQuery qry;
    qry.prepare( "SELECT * FROM teaminfortable" ); //打开一种操作
    qry.exec(); //开始执行操作
    QSqlRecord rec = qry.record();

    int find = 0;
    for(int r = 0; qry.next(); ++r)
    {
        QString nowteam = qry.value(1).toString();
        if(nowteam == teamname)
        {
            teamid = qry.value(0).toString();
            find = 1;
            break ;
        }
    }
    if(teamname == "" || find == 0)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("查看球队信息"), QString::fromLocal8Bit("请在表中选择一支球队进行查看!"), QMessageBox::Yes);
        return ;
    }
    FanViewPlayer fanviewp;
    fanviewp.exec();
}

void FanOper::on_pushButton_6_clicked() //购买球票的退出
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromLocal8Bit("篮球比赛管理系统"), QString::fromLocal8Bit("确定退出?"), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
        exit(0);
}

void FanOper::on_pushButton_5_clicked() //购买球票的返回主菜单
{
    this->close();
}

void FanOper::on_tableView_5_clicked(const QModelIndex &index) //点击viewtable获得要查看到的球队名
{
    int row = ui->tableView_5->currentIndex().row();
    int col = ui->tableView_5->currentIndex().column();

    teamname = scoremodel->data(scoremodel->index(row, col)).toString();
}

void FanOper::on_pushButton_7_clicked() //购买球票
{
    if(buy_hold == "0")
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("购买球票"), QString::fromLocal8Bit("该场比赛球票已售光!"), QMessageBox::Yes);
        return ;
    }
    money = buy_price;
    Buy buy;
    buy.exec();
    int temp = buy_hold.toInt();
    temp--;
    QString newhold = QString::number(temp);

    QSqlQuery qry;
    qry.exec(QString("update ticket set hold = '%1' where team1 = '%2' and team2 = '%3' and hold = '%4' and time = '%5' ").arg(newhold).arg(buy_team1).arg(buy_team2).arg(buy_hold).arg(buy_time) );

    ticketmodel = new QSqlTableModel(this);
    ticketmodel->setTable("ticket");
    ticketmodel->select();
    ui->tableView_6->horizontalHeader()->hide();
    ui->tableView_6->setModel(ticketmodel);
    ui->tableView_6->setColumnWidth(0,70);
    ui->tableView_6->setColumnWidth(1,70);
    ui->tableView_6->setColumnWidth(2,70);
    ui->tableView_6->setColumnWidth(3,72);
    ui->tableView_6->setColumnWidth(4,137);
    ui->tableView_6->setColumnWidth(5,50);
    ui->tableView_6->setColumnWidth(6,50);
    ui->tableView_6->setColumnWidth(7,50);

    qry;
    qry.prepare( "SELECT * FROM ticket" ); //打开一种操作
    qry.exec(); //开始执行操作
    QSqlRecord rec = qry.record();

    QString judge = QString::fromLocal8Bit("在售");
    for(int r = 0; qry.next(); ++r)
    {
        QString nowstatus = qry.value(6).toString();
        QString nowhold = qry.value(7).toString();
        if(nowstatus != judge || nowhold == "0")
        {qDebug() << nowstatus << nowhold;
            ui->tableView_6->setRowHidden(r,1);
        }
    }
}

void FanOper::on_tableView_6_clicked(const QModelIndex &index)
{
    int row = ui->tableView_6->currentIndex().row();

    buy_team1 = ticketmodel->data(ticketmodel->index(row, 0)).toString();
    buy_team2 = ticketmodel->data(ticketmodel->index(row, 1)).toString();
    buy_time = ticketmodel->data(ticketmodel->index(row, 4)).toString();
    buy_price = ticketmodel->data(ticketmodel->index(row, 5)).toString();
    buy_hold = ticketmodel->data(ticketmodel->index(row, 7)).toString();
}
