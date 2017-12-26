#include "manoper.h"
#include "ui_manoper.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSql>
#include <cstring>
#include <iostream>
using namespace std;
#define LL long long

bool a[10005];
int b[15];
int row_price;

void init()
{
    memset(a, 0, sizeof(a));
    for(int i = 0; i < 10000; ++i)
    {
        if((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
            a[i] = 1;
    }
    for(int i = 1; i <= 12; ++i) b[i] = 30;
    b[1] = 31, b[3] = 31, b[5] = 31, b[7] = 31, b[8] = 31, b[10] = 31, b[12] = 31;
}

int get_time(QString ss)
{
    init();
    char *s;
    QByteArray ba = ss.toLatin1();
    s=ba.data();
    int n = strlen(s);
    int d1 = 0, d2, d3, d4;  qDebug() << n;
    for(int i = 0; i < n; ++i)
    {
        if(s[i] == '/')
        {
            if(d1 == 0) d1 = i;
            else d2 = i;
        }
        if(s[i] == 32) d3 = i;
        if(s[i] == ':') d4 = i;
    }
    int year = 0, month = 0, day = 0, hour = 0, min = 0;
    for(int i = 0; i < d1; ++i)
    {
        year *= 10;
        year += s[i] - '0';
    }
    for(int i = d1 + 1; i < d2; ++i)
    {
        month *= 10;
        month += s[i] - '0';
    }
    for(int i = d2 + 1; i < d3; ++i)
    {
        day *= 10;
        day += s[i] - '0';
    }
    for(int i = d3 + 1; i < d4; ++i)
    {
        hour *= 10;
        hour += s[i] - '0';
    }
    for(int i = d4 + 1; i < n; ++i)
    {
        min *= 10;
        min += s[i] - '0';
    }
qDebug() << year << ".." << month << ".." << day << ".." << hour << ".." << min;
    int total = 0;

    for(int i = 0; i < year; ++i)
    {
        if(a[i] == 1) total += 366;
        else total += 365;
    }

    for(int i = 1; i < month; ++i)
    {
        if(i == 2)
        {
            if(a[year]) total += 29;
            else total += 28;
        }
        else total += b[i];
    }

    total += (day - 1);
    total *= 1440;
    total += (hour * 60 + min);
    return total;
}

int judge(QString ss)
{
    char *s;
    QByteArray ba = ss.toLatin1();
    s=ba.data();
    int n = strlen(s);
    int d1 = -1, d2 = -1, d3 = -1, d4 = -1;
    for(int i = 0; i < n; ++i)
    {
        if(s[i] == '/')
        {
            if(d1 == -1) d1 = i;
            else d2 = i;
        }
        if(s[i] == 32) d3 = i;
        if(s[i] == ':') d4 = i;
    }
    if(d1 == -1 || d2 == -1 || d3 == -1 || d4 == -1) return 0;
    else return 1;
}

ManOper::ManOper(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManOper)
{
    ui->setupUi(this);
    this->setFixedSize(700, 433);
    setWindowTitle(QString::fromLocal8Bit("我是管理员!"));
    ui->lineEdit->setFocus(); //鼠标回到用户名栏
    ui->lineEdit_2->setEchoMode(QLineEdit::Password); //输入密码时显示*
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("D:\\VS+QT\\practice\\basketball\\basketball.db");

    if(!db.open())
    {
      qDebug() << db.lastError();
      qFatal("Failed to connect.");
    }
    qDebug("Connected!");

    QSqlQuery qry;

    qry.prepare("create table if not exists scoretable(team1 char(50), score1 char(30), team2 char(50), score2 char(30), gymname char(50), time char(100))");
    if( !qry.exec() )
        qDebug() << qry.lastError();
      else
        qDebug() << "Table created!";

    team1model = new QSqlTableModel(this);
    team1model->setTable("teaminfortable");
    team1model->select();
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->setModel(team1model);
    ui->tableView->setColumnWidth(0,69);
    ui->tableView->setColumnWidth(1,90);
    ui->tableView->setColumnHidden(2,true);
    ui->tableView->setColumnHidden(3,true);
    ui->tableView->setColumnHidden(4,true);

    team2model = new QSqlTableModel(this);
    team2model->setTable("teaminfortable");
    team2model->select();
    ui->tableView_2->horizontalHeader()->hide();
    ui->tableView_2->setModel(team2model);
    ui->tableView_2->setColumnWidth(0,69);
    ui->tableView_2->setColumnWidth(1,90);
    ui->tableView_2->setColumnHidden(2,true);
    ui->tableView_2->setColumnHidden(3,true);
    ui->tableView_2->setColumnHidden(4,true);

    gymmodel = new QSqlTableModel(this);
    gymmodel->setTable("gyminfortable");
    gymmodel->select();
    ui->tableView_3->horizontalHeader()->hide();
    ui->tableView_3->setModel(gymmodel);
    ui->tableView_3->setColumnWidth(0,69);
    ui->tableView_3->setColumnWidth(1,90);
    ui->tableView_3->setColumnHidden(2,true);

    matchmodel = new QSqlTableModel(this);
    matchmodel->setTable("matchtable");
    matchmodel->select();
    ui->tableView_4->horizontalHeader()->hide();
    ui->tableView_4->setModel(matchmodel);
    ui->tableView_4->setColumnWidth(1,90);
    ui->tableView_4->setColumnWidth(2,90);
    ui->tableView_4->setColumnWidth(3,110);
    ui->tableView_4->setColumnWidth(4,129);
    ui->tableView_4->setColumnWidth(5,150);
    ui->tableView_4->setColumnHidden(0,true);

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
}

ManOper::~ManOper()
{
    delete ui;
}

void ManOper::insert_score_table(QString team1, QString team2, QString gym, QString date)
{
    qDebug() << team1 << team2 << gym << date;

    QSqlQuery qry;

    qry.prepare("create table if not exists scoretable(team1 char(50), score1 char(30), team2 char(50), score2 char(30), gymname char(50), time char(100))");
    qry.exec(QString("insert into scoretable(team1, score1, team2, score2, gymname, time) values('%1', '%2', '%3', '%4', '%5', '%6') ").arg(team1).arg("").arg(team2).arg("").arg(gym).arg(date));
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug( "Inserted!" );

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
}

void ManOper::update_score_table(QString team1, QString team2, QString gym, QString date, QString time, QString gym_right)
{
    qDebug() << team1 << team2 << gym << date;

    QSqlQuery qry;

    qry.prepare("create table if not exists scoretable(team1 char(50), score1 char(30), team2 char(50), score2 char(30), gymname char(50), time char(100))");
    qry.exec(QString("update scoretable set gymname = '%1', time = '%2' where time = '%3' and gymname = '%4' ").arg(gym).arg(date).arg(time).arg(gym_right) );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug( "Updated!" );

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
}

void ManOper::update_ticket(QString team1, QString team2, QString gym, QString date, QString time, QString gym_right)
{
    qDebug() << team1 << team2 << gym << date;

    QSqlQuery qry;

    qry.prepare("create table if not exists ticket (team1 char(50), team2 char(50), gymname char(50), gymlocation char(50), time char(50) , price char(50), status char(50), hold integer )");
    qry.exec(QString("update ticket set gymname = '%1', time = '%2' where time = '%3' and gymname = '%4' ").arg(gym).arg(date).arg(time).arg(gym_right) );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug( "Updated!" );

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
}


void ManOper::on_pushButton_clicked() //添加管理员退出
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromLocal8Bit("篮球比赛管理系统"), QString::fromLocal8Bit("确定退出?"), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
        exit(0);
}

void ManOper::on_pushButton_2_clicked() //添加管理员返回主菜单
{
    this->close();
}

void ManOper::on_pushButton_4_clicked() //录入场馆信息退出
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromLocal8Bit("篮球比赛管理系统"), QString::fromLocal8Bit("确定退出?"), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
        exit(0);
}

void ManOper::on_pushButton_3_clicked() //录入场馆信息返回主菜单
{
    this->close();
}

void ManOper::on_pushButton_6_clicked() //管理比赛安排退出
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromLocal8Bit("篮球比赛管理系统"), QString::fromLocal8Bit("确定退出?"), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
        exit(0);
}

void ManOper::on_pushButton_5_clicked() //管理比赛安排返回主菜单
{
    this->close();
}

void ManOper::on_pushButton_8_clicked() //管理球票信息退出
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromLocal8Bit("篮球比赛管理系统"), QString::fromLocal8Bit("确定退出?"), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
        exit(0);
}

void ManOper::on_pushButton_7_clicked() //管理球票信息返回主菜单
{
    this->close();
}

void ManOper::on_pushButton_10_clicked() //发布比赛结果退出
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromLocal8Bit("篮球比赛管理系统"), QString::fromLocal8Bit("确定退出?"), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
        exit(0);
}

void ManOper::on_pushButton_9_clicked() //发布比赛结果返回主菜单
{
    this->close();
}

void ManOper::on_pushButton_11_clicked() //添加管理员
{
    QString num = ui->lineEdit->text();
    QString pass1 = ui->lineEdit_2->text();
    QString pass2 = ui->lineEdit_3->text();

    if(num == "" || pass1 == "" || pass2 == "")
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("添加管理员"), QString::fromLocal8Bit("不能为空!"), QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit->setFocus();
        return ;
    }

    if(pass1 != pass2)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("添加管理员"), QString::fromLocal8Bit("两次输入的密码不一致!"), QMessageBox::Yes);
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_2->setFocus();
        return ;
    }

    QSqlQuery qry;
    qry.prepare( "SELECT * FROM mantable" ); //打开一种操作
    qry.exec(); //开始执行操作
    QSqlRecord rec = qry.record();

    for(int r = 0; qry.next(); ++r)
    {
        QString nowstring = qry.value(0).toString();
        if(nowstring == num)
        {
            QMessageBox::warning(this, QString::fromLocal8Bit("添加管理员"), QString::fromLocal8Bit("该管理员账号已被添加!"), QMessageBox::Yes);
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit->setFocus();
            return ;
        }
    }

    qry.prepare("create table if not exists mantable(number char(30 ) unique primary key, password char(30) ) ");
    qry.exec(QString("insert into mantable(number, password) values('%1', '%2')").arg(num).arg(pass1));

    QMessageBox::information(this, QString::fromLocal8Bit("添加管理员"), QString::fromLocal8Bit("添加成功!"), QMessageBox::Yes);
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit->setFocus();
}

void ManOper::on_pushButton_12_clicked() //录入场馆
{
    QString namee = ui->lineEdit_7->text();
    QString locationn = ui->lineEdit_6->text();
    QString holdd = ui->lineEdit_5->text();

    if(namee == "" || locationn == "" || holdd == "")
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("录入场馆信息"), QString::fromLocal8Bit("不能为空!"), QMessageBox::Yes);
        ui->lineEdit_7->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_7->setFocus();
        return ;
    }

    QSqlQuery qry;
    qry.prepare( "SELECT * FROM gyminfortable" ); //打开一种操作
    qry.exec(); //开始执行操作
    QSqlRecord rec = qry.record();

    for(int r = 0; qry.next(); ++r)
    {
        QString nowstring = qry.value(0).toString();
        if(nowstring == namee)
        {
            QMessageBox::warning(this, QString::fromLocal8Bit("录入场馆信息"), QString::fromLocal8Bit("该场馆信息已录入"), QMessageBox::Yes);
            ui->lineEdit_7->clear();
            ui->lineEdit_6->clear();
            ui->lineEdit_5->clear();
            ui->lineEdit_7->setFocus();
            return ;
        }
    }

    qry.prepare("create table if not exists gyminfortable(name char(50) unique primary key, location char(100), hold char(50)) ");
    qry.exec(QString("insert into gyminfortable(name, location, hold) values('%1', '%2', '%3') ").arg(namee).arg(locationn).arg(holdd));

    QMessageBox::information(this, QString::fromLocal8Bit("录入场馆信息"), QString::fromLocal8Bit("录入成功!"), QMessageBox::Yes);
    ui->lineEdit_7->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_7->setFocus();

    gymmodel = new QSqlTableModel(this);
    gymmodel->setTable("gyminfortable");
    gymmodel->select();
    ui->tableView_3->horizontalHeader()->hide();
    ui->tableView_3->setModel(gymmodel);
    ui->tableView_3->setColumnWidth(0,69);
    ui->tableView_3->setColumnWidth(1,90);
    ui->tableView_3->setColumnHidden(2,true);
}

//void ManOper::on_pushButton_13_clicked() //更新场馆信息
//{
//    QString namee = ui->lineEdit_7->text();
//    QString locationn = ui->lineEdit_6->text();
//    QString holdd = ui->lineEdit_5->text();

//    if(namee == "" || locationn == "" || holdd == "")
//    {
//        QMessageBox::warning(this, QString::fromLocal8Bit("录入场馆信息"), QString::fromLocal8Bit("不能为空!"), QMessageBox::Yes);
//        ui->lineEdit_7->clear();
//        ui->lineEdit_6->clear();
//        ui->lineEdit_5->clear();
//        ui->lineEdit_7->setFocus();
//        return ;
//    }

//    QSqlQuery qry;
//    qry.prepare( "SELECT * FROM gyminfortable" ); //打开一种操作
//    qry.exec(); //开始执行操作
//    QSqlRecord rec = qry.record();

//    int find_gym = 0;
//    for(int r = 0; qry.next(); ++r)
//    {
//        QString nowstring = qry.value(0).toString();
//        if(nowstring == namee)
//            find_gym =1;
//    }
//    if(!find_gym)
//    {
//        QMessageBox::warning(this, QString::fromLocal8Bit("更新场馆信息"), QString::fromLocal8Bit("该场馆信息未录入"), QMessageBox::Yes);
//        ui->lineEdit_7->clear();
//        ui->lineEdit_6->clear();
//        ui->lineEdit_5->clear();
//        ui->lineEdit_7->setFocus();
//        return ;
//    }

//    qry.prepare( "SELECT * FROM ticket" ); //打开一种操作
//    qry.exec(); //开始执行操作
//    rec = qry.record();

//    for(int r = 0; qry.next(); ++r)
//    {
//        QString gym_name = qry.value(2).toString();
//        if(gym_name == namee)
//        {
//            QMessageBox::warning(this, QString::fromLocal8Bit("更新场馆信息"), QString::fromLocal8Bit("在该场馆进行的某场比赛的球票已经发售\n无法更新场馆信息"), QMessageBox::Yes);
//            ui->lineEdit_7->clear();
//            ui->lineEdit_6->clear();
//            ui->lineEdit_5->clear();
//            ui->lineEdit_7->setFocus();
//            return ;
//        }
//    }

//    qry.prepare("create table if not exists gyminfortable(name char(50) unique primary key, location char(100), hold char(50)) ");
//    qry.prepare(QString("update gyminfortable set location = '%1', hold = '%2' where name = '%3' ").arg(locationn).arg(holdd).arg(namee));
//    if( !qry.exec() )
//        qDebug() << qry.lastError();
//    else
//        qDebug( "Updated!" );

//    QMessageBox::information(this, QString::fromLocal8Bit("更新场馆信息"), QString::fromLocal8Bit("更新成功!"), QMessageBox::Yes);
//    ui->lineEdit_7->clear();
//    ui->lineEdit_6->clear();
//    ui->lineEdit_5->clear();
//    ui->lineEdit_7->setFocus();

//    gymmodel = new QSqlTableModel(this);
//    gymmodel->setTable("gyminfortable");
//    gymmodel->select();
//    ui->tableView_3->horizontalHeader()->hide();
//    ui->tableView_3->setModel(gymmodel);
//    ui->tableView_3->setColumnWidth(0,69);
//    ui->tableView_3->setColumnWidth(1,90);
//    ui->tableView_3->setColumnHidden(2,true);

//    //update
//}

void ManOper::on_pushButton_14_clicked() //删除场馆信息
{
    QString namee = ui->lineEdit_7->text();
    QString locationn = ui->lineEdit_6->text();
    QString holdd = ui->lineEdit_5->text();

    if(namee == "")
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("录入场馆信息"), QString::fromLocal8Bit("请输入场馆名!"), QMessageBox::Yes);
        ui->lineEdit_7->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_7->setFocus();
        return ;
    }

    QSqlQuery qry;
    qry.prepare( "SELECT * FROM gyminfortable" ); //打开一种操作
    qry.exec(); //开始执行操作
    QSqlRecord rec = qry.record();

    int find_gym = 0;
    for(int r = 0; qry.next(); ++r)
    {
        QString nowstring = qry.value(0).toString();
        if(nowstring == namee)
            find_gym = 1;
    }
    if(!find_gym)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("删除场馆信息"), QString::fromLocal8Bit("该场馆信息未录入"), QMessageBox::Yes);
        ui->lineEdit_7->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_7->setFocus();
        return ;
    }

    qry.prepare( "SELECT * FROM matchtable" ); //打开一种操作
    qry.exec(); //开始执行操作
    rec = qry.record();
    for(int r = 0; qry.next(); ++r)
    {
        QString nowgym = qry.value(3).toString();
        if(nowgym == namee)
        {
            QMessageBox::warning(this, QString::fromLocal8Bit("删除场馆信息"), QString::fromLocal8Bit("该场馆已举办比赛\n不能删除!"), QMessageBox::Yes);
            ui->lineEdit_7->clear();
            ui->lineEdit_6->clear();
            ui->lineEdit_5->clear();
            ui->lineEdit_7->setFocus();
            return ;
        }
    }

    qry.prepare(QString("delete from gyminfortable where name = '%1' ").arg(namee));
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug( "Deleted!" );

    QMessageBox::information(this, QString::fromLocal8Bit("删除场馆信息"), QString::fromLocal8Bit("删除成功!"), QMessageBox::Yes);
    ui->lineEdit_7->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_7->setFocus();

    gymmodel = new QSqlTableModel(this);
    gymmodel->setTable("gyminfortable");
    gymmodel->select();
    ui->tableView_3->horizontalHeader()->hide();
    ui->tableView_3->setModel(gymmodel);
    ui->tableView_3->setColumnWidth(0,69);
    ui->tableView_3->setColumnWidth(1,90);
    ui->tableView_3->setColumnHidden(2,true);
}

void ManOper::on_pushButton_16_clicked() //修改比赛退出
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromLocal8Bit("篮球比赛管理系统"), QString::fromLocal8Bit("确定退出?"), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
        exit(0);
}

void ManOper::on_pushButton_15_clicked() //修改比赛返回主菜单
{
    this->close();
}

void ManOper::on_tableView_clicked(const QModelIndex &index) //点击球队1表
{
    int row = ui->tableView->currentIndex().row();

    QString team1 = team1model->data(team1model->index(row, 1)).toString();
    qDebug() << team1;

    ui->lineEdit_4->setText(team1);
}

void ManOper::on_tableView_2_clicked(const QModelIndex &index) //点击球队2表
{
    int row = ui->tableView_2->currentIndex().row();

    QString team2 = team2model->data(team2model->index(row, 1)).toString();
    qDebug() << team2;

    ui->lineEdit_8->setText(team2);
}

void ManOper::on_tableView_3_clicked(const QModelIndex &index) //点击场馆表
{
    int row = ui->tableView_3->currentIndex().row();

    QString gym = gymmodel->data(gymmodel->index(row, 0)).toString();
    qDebug() << gym;

    ui->lineEdit_9->setText(gym);
}

void ManOper::on_pushButton_17_clicked() //生成比赛
{
    QString team1 = ui->lineEdit_4->text();
    QString team2 = ui->lineEdit_8->text();
    QString gym = ui->lineEdit_9->text();
    QString date = ui->dateTimeEdit->text();
    qDebug() << date;

    QDateTime dt;
    QTime time;
    QDate datee;
    dt.setTime(time.currentTime());
    dt.setDate(datee.currentDate());
    QString currentDate = dt.toString("yyyy/MM/dd hh:mm");
    qDebug()<<currentDate<<"-=-=-=-=-=-=-=-";

    if(team1 == "" || team2 == "" || gym == "" || date == "")
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("生成比赛"), QString::fromLocal8Bit("不能为空!"), QMessageBox::Yes);
        return ;
    }

    if(team1 == team2)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("生成比赛"), QString::fromLocal8Bit("不能选择同一个队!"), QMessageBox::Yes);
        return ;
    }

    int curtime = get_time(currentDate);
    int settime = get_time(date);
    qDebug() << curtime;
    qDebug() << settime;

    if(settime - curtime > 52560000 || settime <= 0)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("生成比赛"), QString::fromLocal8Bit("请正确设置时间!"), QMessageBox::Yes);
        return ;
    }

    if(settime <= curtime)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("生成比赛"), QString::fromLocal8Bit("比赛时间需大于当前时间!"), QMessageBox::Yes);
        return ;
    }

    QSqlQuery qry;
    qry.prepare("create table if not exists matchtable(digitime integer, team1 char(50), team2 char(50), gymname char(50), gymlocation char(100), time char(100)) ");

    qry.prepare( "SELECT * FROM matchtable" ); //打开一种操作
    qry.exec(); //开始执行操作
    QSqlRecord rec = qry.record();

    for(int r = 0; qry.next(); ++r)
    {
        int nowdigitime = qry.value(0).toInt();
        if((nowdigitime >= settime - 300) && (nowdigitime <= settime + 300))
        {
            QString nowgym = qry.value(3).toString();
            if(nowgym == gym)
            {
                QMessageBox::warning(this, QString::fromLocal8Bit("生成比赛"), QString::fromLocal8Bit("该场馆在该时间的五小时内已有比赛\n请设置其他时间或选择其他场馆"), QMessageBox::Yes);
                return ;
            }
            QString nowteam1 = qry.value(1).toString();
            QString nowteam2 = qry.value(2).toString();
            if(nowteam1 == team1 || nowteam2 == team1)
            {
                QMessageBox::warning(this, QString::fromLocal8Bit("生成比赛"), QString::fromLocal8Bit("队伍1在该时间的五小时内已有比赛\n请设置其他时间"), QMessageBox::Yes);
                return ;
            }
            if(nowteam1 == team2 || nowteam2 == team2)
            {
                QMessageBox::warning(this, QString::fromLocal8Bit("生成比赛"), QString::fromLocal8Bit("队伍2在该时间的五小时内已有比赛\n请设置其他时间"), QMessageBox::Yes);
                return ;
            }
        }
    }


    //参加比赛的每支球队至少有5名球员
    qry.prepare( "SELECT * FROM teaminfortable" ); //打开一种操作
    qry.exec(); //开始执行操作
    rec = qry.record();
    QString id1, id2;
    for(int r = 0; qry.next(); ++r)
    {
        QString nowteam = qry.value(1).toString();
        if(nowteam == team1)
        {
            id1 = qry.value(0).toString();
            break;
        }
    }
    qry.prepare( "SELECT * FROM playerinfortable" ); //打开一种操作
    qry.exec(); //开始执行操作
    rec = qry.record();
    int cnts1 = 0;
    for(int r = 0; qry.next(); ++r)
    {
        QString nowid = qry.value(1).toString();
        if(nowid == id1)
            cnts1++;
    }
    if(cnts1 < 5)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("生成比赛"), QString::fromLocal8Bit("球队1至少有5名球员才能参加比赛!"), QMessageBox::Yes);
        return ;
    }

    qry.prepare( "SELECT * FROM teaminfortable" ); //打开一种操作
    qry.exec(); //开始执行操作
    rec = qry.record();
    for(int r = 0; qry.next(); ++r)
    {
        QString nowteam = qry.value(1).toString();
        if(nowteam == team2)
        {
            id2 = qry.value(0).toString();
            break;
        }
    }
    qry.prepare( "SELECT * FROM playerinfortable" ); //打开一种操作
    qry.exec(); //开始执行操作
    rec = qry.record();
    int cnts2 = 0;
    for(int r = 0; qry.next(); ++r)
    {
        QString nowid = qry.value(1).toString();
        if(nowid == id1)
            cnts2++;
    }
    if(cnts2 < 5)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("生成比赛"), QString::fromLocal8Bit("球队2至少有5名球员才能参加比赛!"), QMessageBox::Yes);
        return ;
    }

    int row = ui->tableView_3->currentIndex().row();

    QString location = gymmodel->data(gymmodel->index(row, 1)).toString();

    qDebug() << settime << team1 << team2 << gym << location << date;


    //不能有相同时间的比赛
    qry.prepare( "SELECT * FROM matchtable" ); //打开一种操作
    qry.exec(); //开始执行操作
    rec = qry.record();

    for(int r = 0; qry.next(); ++r)
    {
        QString nowtime = qry.value(5).toString();
        if(nowtime == date)
        {
            QMessageBox::warning(this, QString::fromLocal8Bit("生成比赛"), QString::fromLocal8Bit("该时间已有比赛!\n"), QMessageBox::Yes);
            return ;
        }
    }


    qry.exec(QString("insert into matchtable(digitime, team1, team2, gymname, gymlocation, time) values( %1, '%2', '%3', '%4', '%5', '%6' ) ").arg(settime).arg(team1).arg(team2).arg(gym).arg(location).arg(date) );

    QMessageBox::warning(this, QString::fromLocal8Bit("生成比赛"), QString::fromLocal8Bit("生成成功!"), QMessageBox::Yes);

    //找出场馆的容纳人数
    qry.prepare( "SELECT * FROM gyminfortable" ); //打开一种操作
    qry.exec(); //开始执行操作
    rec = qry.record();

    int hold;
    for(int r = 0; qry.next(); ++r)
    {
        QString nowgym = qry.value(0).toString();
        if(nowgym == gym)
        {
            hold = qry.value(2).toInt();
            break;
        }
    }

    qry.exec(QString("insert into ticket (team1, team2, gymname, gymlocation, time, hold ) values( '%1', '%2', '%3', '%4', '%5' ,%6 ) ").arg(team1).arg(team2).arg(gym).arg(location).arg(date).arg(hold) );

    ui->lineEdit_4->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();

    matchmodel = new QSqlTableModel(this);
    matchmodel->setTable("matchtable");
    matchmodel->select();
    ui->tableView_4->horizontalHeader()->hide();
    ui->tableView_4->setModel(matchmodel);
    ui->tableView_4->setColumnWidth(1,90);
    ui->tableView_4->setColumnWidth(2,90);
    ui->tableView_4->setColumnWidth(3,110);
    ui->tableView_4->setColumnWidth(4,129);
    ui->tableView_4->setColumnWidth(5,150);
    ui->tableView_4->setColumnHidden(0,true);

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

    insert_score_table(team1, team2, gym, date);
}

void ManOper::on_pushButton_19_clicked() //删除比赛
{
    int row = ui->tableView_4->currentIndex().row();

    QString timee = matchmodel->data(matchmodel->index(row, 5)).toString();
    QString gymm = matchmodel->data(matchmodel->index(row, 3)).toString();

    QSqlQuery qry;
    qry.prepare( "SELECT * FROM ticket" ); //打开一种操作
    qry.exec(); //开始执行操作
    QSqlRecord rec = qry.record();

    for(int r = 0; qry.next(); ++r)
    {
        QString statuss = qry.value(6).toString();
        QString ticket_time = qry.value(4).toString();
        QString judge = QString::fromLocal8Bit("在售");
        if(statuss == judge && timee == ticket_time)
        {
            QMessageBox::warning(this, QString::fromLocal8Bit("修改比赛"), QString::fromLocal8Bit("该场比赛的球票已经发售\n不能修改比赛"), QMessageBox::Yes);
            ui->lineEdit_10->clear();
            ui->lineEdit_11->clear();
            ui->lineEdit_12->clear();
            ui->lineEdit_13->clear();
            return ;
        }
    }

    qry.prepare( "SELECT * FROM ticket" ); //打开一种操作
    qry.exec(); //开始执行操作
    rec = qry.record();

    for(int r = 0; qry.next(); ++r)
    {
        QString nowtime = qry.value(4).toString();
        QString judge = QString::fromLocal8Bit("在售");
        QString nowstatus = qry.value(6).toString();

        if(nowtime == timee && judge == nowstatus)
        {
            QMessageBox::information(this, QString::fromLocal8Bit("删除比赛"), QString::fromLocal8Bit("该场比赛球票已经发售\n无法删除比赛"), QMessageBox::Yes);
            ui->lineEdit_10->clear();
            ui->lineEdit_11->clear();
            ui->lineEdit_12->clear();
            ui->lineEdit_13->clear();
            return ;
        }
    }

    qry.prepare( "SELECT * FROM matchtable" ); //打开一种操作
    qry.exec(); //开始执行操作
    rec = qry.record();

    qry.prepare(QString("delete from matchtable where time = '%1' and gymname = '%2' ").arg(timee).arg(gymm));
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug( "Deleted!" );

    QMessageBox::information(this, QString::fromLocal8Bit("删除比赛"), QString::fromLocal8Bit("删除成功!"), QMessageBox::Yes);
    ui->lineEdit_10->clear();
    ui->lineEdit_11->clear();
    ui->lineEdit_12->clear();
    ui->lineEdit_13->clear();

    matchmodel = new QSqlTableModel(this);
    matchmodel->setTable("matchtable");
    matchmodel->select();
    ui->tableView_4->horizontalHeader()->hide();
    ui->tableView_4->setModel(matchmodel);
    ui->tableView_4->setColumnWidth(1,90);
    ui->tableView_4->setColumnWidth(2,90);
    ui->tableView_4->setColumnWidth(3,110);
    ui->tableView_4->setColumnWidth(4,129);
    ui->tableView_4->setColumnWidth(5,150);
    ui->tableView_4->setColumnHidden(0,true);

    qry.prepare( "SELECT * FROM scoretable" ); //打开一种操作
    qry.exec(); //开始执行操作
    rec = qry.record();

    for(int r = 0; qry.next(); ++r)
    {
        QString nowtime = qry.value(5).toString();

        if(nowtime == timee)
        {
            QString nowgym = qry.value(4).toString();
            qry.prepare(QString("delete from scoretable where time = '%1' and gymname = '%2' ").arg(timee).arg(nowgym));
            qry.exec();
            break;
        }
    }

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

    qry.prepare( "SELECT * FROM ticket" ); //打开一种操作
    qry.exec(); //开始执行操作
    rec = qry.record();

    for(int r = 0; qry.next(); ++r)
    {
        QString nowtime = qry.value(4).toString();

        if(nowtime == timee)
        {
            QString nowgym = qry.value(2).toString();
            qry.prepare(QString("delete from ticket where time = '%1' and gymname = '%2' ").arg(timee).arg(nowgym));
            qry.exec();
            break;
        }
    }

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
}

void ManOper::on_tableView_4_clicked(const QModelIndex &index)
{
    int row = ui->tableView_4->currentIndex().row();

    QString team1 = matchmodel->data(matchmodel->index(row, 1)).toString();
//    qDebug() << team1;
    QString team2 = matchmodel->data(matchmodel->index(row, 2)).toString();
    QString gym = matchmodel->data(matchmodel->index(row, 3)).toString();
    QString time = matchmodel->data(matchmodel->index(row, 5)).toString();

    ui->lineEdit_10->setText(team1);
    ui->lineEdit_11->setText(team2);
    ui->lineEdit_12->setText(gym);
    ui->lineEdit_13->setText(time);
}

void ManOper::on_pushButton_18_clicked() //修改比赛
{
    QString team1 = ui->lineEdit_10->text();
    QString team2 = ui->lineEdit_11->text();
    QString gym = ui->lineEdit_12->text();
    QString date = ui->lineEdit_13->text();

    int row = ui->tableView_4->currentIndex().row();
    QString team1_right = matchmodel->data(matchmodel->index(row, 1)).toString();
    QString team2_right = matchmodel->data(matchmodel->index(row, 2)).toString();
    QString digitimee = matchmodel->data(matchmodel->index(row, 0)).toInt();
    QString time_right = matchmodel->data(matchmodel->index(row, 5)).toString();
    QString gym_right = matchmodel->data(matchmodel->index(row, 3)).toString();
//    qDebug() << digitimee;

    if(team1 != team1_right || team2 != team2_right)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("修改比赛"), QString::fromLocal8Bit("请勿改动比赛球队"), QMessageBox::Yes);
        ui->lineEdit_10->setText(team1_right);
        ui->lineEdit_11->setText(team2_right);
        return ;
    }

    if(gym == "" || date == "")
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("修改比赛"), QString::fromLocal8Bit("不能为空!"), QMessageBox::Yes);
        return ;
    }

    QSqlQuery qry;
    qry.prepare( "SELECT * FROM gyminfortable" ); //打开一种操作
    qry.exec(); //开始执行操作
    QSqlRecord rec = qry.record();

    int find_gym = 0;
    for(int r = 0; qry.next(); ++r)
    {
        QString gymm = qry.value(0).toString();
        if(gymm == gym) find_gym = 1;
    }
    if(!find_gym)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("修改比赛"), QString::fromLocal8Bit("该场馆未录入!"), QMessageBox::Yes);
        ui->lineEdit_12->clear();
        ui->lineEdit_12->setFocus();
        return ;
    }

    if(!judge(date))
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("修改比赛"), QString::fromLocal8Bit("请按 YYYY/MM/DD HH:MM 格式输入时间!"), QMessageBox::Yes);
        return ;
    }

    else
    {
        int nowdigi = get_time(date);

        //计算当前时间
        QDateTime dt;
        QTime time;
        QDate datee;
        dt.setTime(time.currentTime());
        dt.setDate(datee.currentDate());
        QString currentDate = dt.toString("yyyy/MM/dd hh:mm");

        int right_now = get_time(currentDate);

        if(nowdigi - right_now > 52560000 || nowdigi <= 0)
        {
            QMessageBox::warning(this, QString::fromLocal8Bit("修改比赛"), QString::fromLocal8Bit("请正确设置时间!"), QMessageBox::Yes);
            return ;
        }

//        if(nowdigi < right_now)
//        {
//            QMessageBox::warning(this, QString::fromLocal8Bit("修改比赛"), QString::fromLocal8Bit("比赛时间需大于当前时间!"), QMessageBox::Yes);
//            return ;
//        }
        QSqlQuery qry;
        qry.prepare( "SELECT * FROM matchtable" ); //打开一种操作
        qry.exec(); //开始执行操作
        QSqlRecord rec = qry.record();

        for(int r = 0; qry.next(); ++r)
        {
            QString judgetime = qry.value(5).toString();
            if(judgetime == time_right) continue;

            int nowdigitime = qry.value(0).toInt();
            qDebug() << nowdigitime << ".." << nowdigi;
            if((nowdigitime >= nowdigi - 300) && (nowdigitime <= nowdigi + 300))
            {
                QString nowgym = qry.value(3).toString();
                if(nowgym == gym)
                {
                    QMessageBox::warning(this, QString::fromLocal8Bit("修改比赛"), QString::fromLocal8Bit("该场馆在该时间的五小时内已有比赛\n请设置其他时间或选择其他场馆"), QMessageBox::Yes);
                    return ;
                }
                QString nowteam1 = qry.value(1).toString();
                QString nowteam2 = qry.value(2).toString();
                if(nowteam1 == team1 || nowteam2 == team1)
                {
                    QMessageBox::warning(this, QString::fromLocal8Bit("修改比赛"), QString::fromLocal8Bit("队伍1在该时间的五小时内已有比赛\n请设置其他时间"), QMessageBox::Yes);
                    return ;
                }
                if(nowteam1 == team2 || nowteam2 == team2)
                {
                    QMessageBox::warning(this, QString::fromLocal8Bit("修改比赛"), QString::fromLocal8Bit("队伍2在该时间的五小时内已有比赛\n请设置其他时间"), QMessageBox::Yes);
                    return ;
                }
            }
        }

        qry.prepare( "SELECT * FROM ticket" ); //打开一种操作
        qry.exec(); //开始执行操作
        rec = qry.record();

        for(int r = 0; qry.next(); ++r)
        {
            QString statuss = qry.value(6).toString();
            QString ticket_time = qry.value(4).toString();
            qDebug() << statuss;
            QString judge = QString::fromLocal8Bit("在售");
            if(statuss == judge && time_right == ticket_time)
            {
                QMessageBox::warning(this, QString::fromLocal8Bit("修改比赛"), QString::fromLocal8Bit("该场比赛的球票已经发售\n不能修改比赛"), QMessageBox::Yes);
                ui->lineEdit_10->clear();
                ui->lineEdit_11->clear();
                ui->lineEdit_12->clear();
                ui->lineEdit_13->clear();
                return ;
            }
        }

        qry.prepare("create table if not exists matchtable(digitime integer, team1 char(50), team2 char(50), gymname char(50), gymlocation char(100), time char(100)) ");
        qry.prepare(QString("update matchtable set digitime = '%1', team1 = '%2', team2 = '%3', gymname = '%4', time = '%5' where time = '%6' and gymname = '%7' ").arg(nowdigi).arg(team1).arg(team2).arg(gym).arg(date).arg(time_right).arg(gym_right));
        if( !qry.exec() )
            qDebug() << qry.lastError();
        else
            qDebug( "Updated!" );

        QMessageBox::information(this, QString::fromLocal8Bit("修改比赛"), QString::fromLocal8Bit("修改成功!"), QMessageBox::Yes);
        ui->lineEdit_10->clear();
        ui->lineEdit_11->clear();
        ui->lineEdit_12->clear();
        ui->lineEdit_13->clear();

        matchmodel = new QSqlTableModel(this);
        matchmodel->setTable("matchtable");
        matchmodel->select();
        ui->tableView_4->horizontalHeader()->hide();
        ui->tableView_4->setModel(matchmodel);
        ui->tableView_4->setColumnWidth(1,90);
        ui->tableView_4->setColumnWidth(2,90);
        ui->tableView_4->setColumnWidth(3,110);
        ui->tableView_4->setColumnWidth(4,129);
        ui->tableView_4->setColumnWidth(5,150);
        ui->tableView_4->setColumnHidden(0,true);

        update_score_table(team1, team2, gym, date, time_right, gym_right);

        update_ticket(team1, team2, gym, date, time_right, gym_right);
    }
}

void ManOper::on_tableView_5_clicked(const QModelIndex &index)
{
    int row = ui->tableView_5->currentIndex().row();

    QString team1 = scoremodel->data(scoremodel->index(row, 0)).toString();
    QString team2 = scoremodel->data(scoremodel->index(row, 2)).toString();

    ui->lineEdit_14->setText(team1);
    ui->lineEdit_15->setText(team2);
}

void ManOper::on_pushButton_20_clicked() //发布比赛结果
{
    int row = ui->tableView_5->currentIndex().row();

    QString team1 = scoremodel->data(scoremodel->index(row, 0)).toString();
    QString team2 = scoremodel->data(scoremodel->index(row, 2)).toString();
    QString matchtime = scoremodel->data(scoremodel->index(row, 5)).toString();
    QString nowgym = scoremodel->data(scoremodel->index(row, 4)).toString();

    ui->lineEdit_14->setText(team1);
    ui->lineEdit_15->setText(team2);

    QString s1 = ui->lineEdit_16->text();
    QString s2 = ui->lineEdit_17->text();

    QDateTime dt;
    QTime time;
    QDate datee;
    dt.setTime(time.currentTime());
    dt.setDate(datee.currentDate());
    QString currenttime = dt.toString("yyyy/MM/dd hh:mm");

    int match_time = get_time(matchtime);
    int current_time = get_time(currenttime);

    if(current_time <= match_time)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("发布比赛结果"), QString::fromLocal8Bit("该场比赛还未进行!"), QMessageBox::Yes);
        ui->lineEdit_14->clear();
        ui->lineEdit_15->clear();
        ui->lineEdit_16->clear();
        ui->lineEdit_17->clear();
        return ;
    }

    if(s1 == "" || s2 == "")
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("发布比赛结果"), QString::fromLocal8Bit("不能为空!"), QMessageBox::Yes);
        return ;
    }

    if(s1 == s2)
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("发布比赛结果"), QString::fromLocal8Bit("请输入正确比分!"), QMessageBox::Yes);
        ui->lineEdit_16->clear();
        ui->lineEdit_17->clear();
        return ;
    }

    QSqlQuery qry;
    qry.prepare("create table if not exists scoretable(team1 char(50), score1 char(30), team2 char(50), score2 char(30), gymname char(50), time char(100))");
    qry.exec(QString("update scoretable set score1 = '%1', score2 = '%2' where time = '%3' and gymname = '%4' ").arg(s1).arg(s2).arg(matchtime).arg(nowgym) );

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
}

void ManOper::on_pushButton_21_clicked() //输入价格，发售球票
{
    QString pricee = ui->lineEdit_18->text();
    QString timee = ticketmodel->data(ticketmodel->index(row_price, 4)).toString();
    QString nowgym = ticketmodel->data(ticketmodel->index(row_price, 2)).toString();
    qDebug() << timee << nowgym;
    QSqlQuery qry;
    qry.exec(QString("update ticket set price = '%1', status = '%2' where gymname = '%3' and time = '%4' ").arg(pricee).arg(QString::fromLocal8Bit("在售")).arg(nowgym).arg(timee) );
    ui->lineEdit_18->clear();

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
}

void ManOper::on_tableView_6_clicked(const QModelIndex &index)
{
    row_price = ui->tableView_6->currentIndex().row();
}
