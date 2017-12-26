#include "teamoper.h"
#include "ui_teamoper.h"
#include "viewplayer.h"
#include "viewteam.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSql>

int opent = 0, openp = 0;

TeamOper::TeamOper(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeamOper)
{
    ui->setupUi(this);
    this->setFixedSize(700, 433);
    setWindowTitle(QString::fromLocal8Bit("我是球队!"));
    ui->lineEdit_8->setFocus(); //鼠标回到用户名栏
    ui->lineEdit_13->setEchoMode(QLineEdit::Password); //输入密码时显示*
    ui->lineEdit_7->setEchoMode(QLineEdit::Password);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("D:\\VS+QT\\practice\\basketball\\basketball.db");

    if(!db.open())
    {
      qDebug() << db.lastError();
      qFatal("Failed to connect.");
    }
    qDebug("Connected!");
}

TeamOper::~TeamOper()
{
    delete ui;
}

void TeamOper::on_pushButton_6_clicked() //录入球队退出
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromLocal8Bit("篮球比赛管理系统"), QString::fromLocal8Bit("确定退出?"), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
        exit(0);
}

void TeamOper::on_pushButton_5_clicked() //录入球队返回主菜单
{
    if(opent)
    {
        viewt->close();
        delete viewt;
        opent = 0;
    }
    if(openp)
    {
        viewp->close();
        delete viewp;
        openp = 0;
    }
    this->close();
}

void TeamOper::on_pushButton_8_clicked() //录入球员退出
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromLocal8Bit("篮球比赛管理系统"), QString::fromLocal8Bit("确定退出?"), QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
        exit(0);
}

void TeamOper::on_pushButton_7_clicked() //录入球员返回主菜单
{
    if(openp)
    {
        viewp->close();
        delete viewp;
        openp = 0;
    }
    if(opent)
    {
        viewt->close();
        delete viewt;
        opent = 0;
    }
    this->close();
}

void TeamOper::on_pushButton_clicked() //球队信息录入
{
    QString idd = ui->lineEdit_8->text();
    QString namee = ui->lineEdit_9->text();
    QString companyy = ui->lineEdit_10->text();
    QString managerr = ui->lineEdit_11->text();
    QString coachh = ui->lineEdit_12->text();
    QString test = ui->lineEdit_13->text();

    if(idd == "" || namee == "" || companyy == "" || managerr == "" || coachh == "")
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("录入球队信息"), QString::fromLocal8Bit("不能为空!"), QMessageBox::Yes);
        ui->lineEdit_8->clear();
        ui->lineEdit_9->clear();
        ui->lineEdit_10->clear();
        ui->lineEdit_11->clear();
        ui->lineEdit_12->clear();
        ui->lineEdit_13->clear();
        ui->lineEdit_8->setFocus();
        return ;
    }

    if(test == "qtqtqt")
    {
        QSqlQuery qry;
        qry.prepare( "SELECT * FROM teaminfortable" ); //打开一种操作
        qry.exec(); //开始执行操作
        QSqlRecord rec = qry.record();

        for(int r = 0; qry.next(); ++r)
        {
            QString nowstring = qry.value(0).toString();
            if(nowstring == idd)
            {
                QMessageBox::warning(this, QString::fromLocal8Bit("录入球队信息"), QString::fromLocal8Bit("该球队信息已录入"), QMessageBox::Yes);
                ui->lineEdit_8->clear();
                ui->lineEdit_9->clear();
                ui->lineEdit_10->clear();
                ui->lineEdit_11->clear();
                ui->lineEdit_12->clear();
                ui->lineEdit_13->clear();
                ui->lineEdit_8->setFocus();
                return ;
            }
        }

        qry.prepare("create table if not exists teaminfortable(id char(30) unique primary key, name char(50), company char(50), manager char(50), coach char(50))");
        qry.exec(QString("insert into teaminfortable(id, name, company, manager, coach) values('%1', '%2', '%3', '%4', '%5')").arg(idd).arg(namee).arg(companyy).arg(managerr).arg(coachh));

        QMessageBox::information(this, QString::fromLocal8Bit("录入球队信息"), QString::fromLocal8Bit("录入成功!"), QMessageBox::Yes);
        ui->lineEdit_8->clear();
        ui->lineEdit_9->clear();
        ui->lineEdit_10->clear();
        ui->lineEdit_11->clear();
        ui->lineEdit_12->clear();
        ui->lineEdit_13->clear();
        ui->lineEdit_8->setFocus();
    }

    else
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("录入球队信息"), QString::fromLocal8Bit("验证密码错误!"), QMessageBox::Yes);
        ui->lineEdit_13->clear();
        ui->lineEdit_13->setFocus();
    }
}

//void TeamOper::on_pushButton_2_clicked() //更新球队信息
//{
//    QString idd = ui->lineEdit_8->text();
//    QString namee = ui->lineEdit_9->text();
//    QString companyy = ui->lineEdit_10->text();
//    QString managerr = ui->lineEdit_11->text();
//    QString coachh = ui->lineEdit_12->text();
//    QString test = ui->lineEdit_13->text();

//    if(idd == "" || namee == "" || companyy == "" || managerr == "" || coachh == "")
//    {
//        QMessageBox::warning(this, QString::fromLocal8Bit("更新球队信息"), QString::fromLocal8Bit("不能为空!"), QMessageBox::Yes);
//        ui->lineEdit_8->clear();
//        ui->lineEdit_9->clear();
//        ui->lineEdit_10->clear();
//        ui->lineEdit_11->clear();
//        ui->lineEdit_12->clear();
//        ui->lineEdit_13->clear();
//        ui->lineEdit_8->setFocus();
//        return ;
//    }

//    if(test == "qtqtqt")
//    {
//        QSqlQuery qry;
//        qry.prepare( "SELECT * FROM teaminfortable" ); //打开一种操作
//        qry.exec(); //开始执行操作
//        QSqlRecord rec = qry.record();

//        int flag = 0;
//        QString teamname;
//        for(int r = 0; qry.next(); ++r)
//        {
//            QString nowstring = qry.value(0).toString();
//            if(nowstring == idd)
//            {
//                teamname = qry.value(1).toString();
//                flag = 1;
//                break;
//            }
//        }
//        if(!flag)
//        {
//            QMessageBox::warning(this, QString::fromLocal8Bit("更新球队信息"), QString::fromLocal8Bit("该球队信息未录入\n请先录入"), QMessageBox::Yes);
//            return ;
//        }

//        qry.prepare( "SELECT * FROM ticket" ); //打开一种操作
//        qry.exec(); //开始执行操作
//        rec = qry.record();

//        for(int r = 0; qry.next(); ++r)
//        {
//            QString statuss = qry.value(6).toString();
//            QString team1 = qry.value(0).toString();
//            QString team2 = qry.value(1).toString();
//            QString judge = QString::fromLocal8Bit("在售");
//            if(statuss == judge && (teamname == team1 || teamname ==team2) )
//            {
//                QMessageBox::warning(this, QString::fromLocal8Bit("修改球队"), QString::fromLocal8Bit("该场比赛的球票已经发售\n不能修改比赛"), QMessageBox::Yes);
//                ui->lineEdit_8->clear();
//                ui->lineEdit_9->clear();
//                ui->lineEdit_10->clear();
//                ui->lineEdit_11->clear();
//                ui->lineEdit_12->clear();
//                ui->lineEdit_13->clear();
//                ui->lineEdit_8->setFocus();
//                return ;
//            }
//        }

//        qry.prepare(QString("update teaminfortable set name = '%1', company = '%2', manager = '%3', coach = '%4' where id = '%5' ").arg(namee).arg(companyy).arg(managerr).arg(coachh).arg(idd));
//        if( !qry.exec() )
//            qDebug() << qry.lastError();
//        else
//            qDebug( "Updated!" );

//        QMessageBox::information(this, QString::fromLocal8Bit("更新球队信息"), QString::fromLocal8Bit("更新成功!"), QMessageBox::Yes);
//        ui->lineEdit_8->clear();
//        ui->lineEdit_9->clear();
//        ui->lineEdit_10->clear();
//        ui->lineEdit_11->clear();
//        ui->lineEdit_12->clear();
//        ui->lineEdit_13->clear();
//        ui->lineEdit_8->setFocus();
//    }

//    else
//    {
//        QMessageBox::warning(this, QString::fromLocal8Bit("更新球队信息"), QString::fromLocal8Bit("验证密码错误!"), QMessageBox::Yes);
//        ui->lineEdit_13->clear();
//        ui->lineEdit_13->setFocus();
//    }
//}

void TeamOper::on_pushButton_3_clicked() //录入球员信息
{
    QString idd = ui->lineEdit->text();
    QString playeridd = ui->lineEdit_14->text();
    QString namee = ui->lineEdit_2->text();
    QString agee = ui->lineEdit_3->text();
    QString talll = ui->lineEdit_4->text();
    QString weightt = ui->lineEdit_5->text();
    QString poss = ui->lineEdit_6->text();
    QString test = ui->lineEdit_7->text();

    if(idd == "" || playeridd == "" || namee == "" || agee == "" || talll == "" || weightt == "" || poss == "")
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("录入球员信息"), QString::fromLocal8Bit("不能为空!"), QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit_14->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_14->setFocus();
        return ;
    }

    if(test == "qtqtqt")
    {
        QSqlQuery qry;
        qry.prepare( "SELECT * FROM playerinfortable" ); //打开一种操作
        qry.exec(); //开始执行操作
        QSqlRecord rec = qry.record();

        for(int r = 0; qry.next(); ++r)
        {
            QString nowstring = qry.value(0).toString();
            if(nowstring == playeridd)
            {
                QMessageBox::warning(this, QString::fromLocal8Bit("录入球员信息"), QString::fromLocal8Bit("该球员信息已录入"), QMessageBox::Yes);
                ui->lineEdit->clear();
                ui->lineEdit_14->clear();
                ui->lineEdit_2->clear();
                ui->lineEdit_3->clear();
                ui->lineEdit_4->clear();
                ui->lineEdit_5->clear();
                ui->lineEdit_6->clear();
                ui->lineEdit_7->clear();
                ui->lineEdit_14->setFocus();
                return ;
            }
        }

        int find_team = 0;
        qry.prepare( "SELECT * FROM teaminfortable" ); //打开一种操作
        qry.exec(); //开始执行操作
        rec = qry.record();

        for(int r = 0; qry.next(); ++r)
        {
            QString nowteam = qry.value(0).toString();
            if(nowteam == idd) find_team = 1;
        }
        if(!find_team)
        {
            QMessageBox::warning(this, QString::fromLocal8Bit("录入球员信息"), QString::fromLocal8Bit("该球队信息未录入\n请先录入球队信息"), QMessageBox::Yes);
            ui->lineEdit->clear();
            ui->lineEdit_14->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
            ui->lineEdit_5->clear();
            ui->lineEdit_6->clear();
            ui->lineEdit_7->clear();
            ui->lineEdit_14->setFocus();
            return ;
        }

        qry.prepare("create table if not exists playerinfortable(playerid char(30) unique primary key, id char(30), name char(50), age char(30), tall char(30), weight char(30), pos char(30))");
        qry.exec(QString("insert into playerinfortable(playerid, id, name, age, tall, weight, pos) values('%1', '%2', '%3', '%4', '%5', '%6', '%7') ").arg(playeridd).arg(idd).arg(namee).arg(agee).arg(talll).arg(weightt).arg(poss));

        QMessageBox::information(this, QString::fromLocal8Bit("录入球员信息"), QString::fromLocal8Bit("录入成功!"), QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit_14->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_14->setFocus();
    }

    else
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("录入球员信息"), QString::fromLocal8Bit("验证密码错误!"), QMessageBox::Yes);
        ui->lineEdit_7->clear();
        ui->lineEdit_7->setFocus();
    }
}

void TeamOper::on_pushButton_9_clicked() //删除球员信息
{
    QString playeridd = ui->lineEdit_14->text();
    QString test = ui->lineEdit_7->text();

    if(playeridd == "")
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("删除球员信息"), QString::fromLocal8Bit("请输入球员编号!"), QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit_14->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_14->setFocus();
        return ;
    }

    if(test == "qtqtqt")
    {
        QSqlQuery qry;
        qry.prepare( "SELECT * FROM playerinfortable" ); //打开一种操作
        qry.exec(); //开始执行操作
        QSqlRecord rec = qry.record();

        int find_player = 0;
        QString teamid;
        for(int r = 0; qry.next(); ++r)
        {
            QString nowstring = qry.value(0).toString();
            if(nowstring == playeridd)
            {
                find_player = 1;
                teamid = qry.value(1).toString();
            }
        }
        if(!find_player)
        {
            QMessageBox::warning(this, QString::fromLocal8Bit("删除球员信息"), QString::fromLocal8Bit("该球员信息未录入"), QMessageBox::Yes);
            ui->lineEdit->clear();
            ui->lineEdit_14->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
            ui->lineEdit_5->clear();
            ui->lineEdit_6->clear();
            ui->lineEdit_7->clear();
            ui->lineEdit_14->setFocus();
            return ;
        }


        qry.prepare( "SELECT * FROM teaminfortable" ); //打开一种操作
        qry.exec(); //开始执行操作
        rec = qry.record();

        QString teamname;
        for(int r = 0; qry.next(); ++r)
        {
            QString nowstring = qry.value(0).toString();
            if(nowstring == teamid)
            {
                teamname = qry.value(1).toString();
                break;
            }
        }

        qDebug() << teamname;
        //已经生成比赛的球队不能删除
        qry.prepare( "SELECT * FROM matchtable" ); //打开一种操作
        qry.exec(); //开始执行操作
        rec = qry.record();
        for(int r = 0; qry.next(); ++r)
        {
            QString nowteam1 = qry.value(1).toString();
            QString nowteam2 = qry.value(2).toString();
            if(nowteam1 == teamname)
            {
                QMessageBox::warning(this, QString::fromLocal8Bit("删除球员信息"), QString::fromLocal8Bit("该球员所在球队已参加比赛\n不能删除!"), QMessageBox::Yes);
                ui->lineEdit->clear();
                ui->lineEdit_14->clear();
                ui->lineEdit_2->clear();
                ui->lineEdit_3->clear();
                ui->lineEdit_4->clear();
                ui->lineEdit_5->clear();
                ui->lineEdit_6->clear();
                ui->lineEdit_7->clear();
                ui->lineEdit_14->setFocus();
                return ;
            }
            if(nowteam2 == teamname)
            {
                QMessageBox::warning(this, QString::fromLocal8Bit("删除球员信息"), QString::fromLocal8Bit("该球员所在球队已参加比赛\n不能删除!"), QMessageBox::Yes);
                ui->lineEdit->clear();
                ui->lineEdit_14->clear();
                ui->lineEdit_2->clear();
                ui->lineEdit_3->clear();
                ui->lineEdit_4->clear();
                ui->lineEdit_5->clear();
                ui->lineEdit_6->clear();
                ui->lineEdit_7->clear();
                ui->lineEdit_14->setFocus();
                return ;
            }
        }

        qry.prepare(QString("delete from playerinfortable where playerid = '%1' ").arg(playeridd));
        if( !qry.exec() )
            qDebug() << qry.lastError();
        else
            qDebug( "Deleted!" );

        QMessageBox::information(this, QString::fromLocal8Bit("删除球员信息"), QString::fromLocal8Bit("删除成功!"), QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit_14->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        ui->lineEdit_14->setFocus();
    }

    else
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("删除球员信息"), QString::fromLocal8Bit("验证密码错误!"), QMessageBox::Yes);
        ui->lineEdit_7->clear();
        ui->lineEdit_7->setFocus();
    }
}

//void TeamOper::on_pushButton_4_clicked() //更新球员信息
//{
//    QString idd = ui->lineEdit->text();
//    QString playeridd = ui->lineEdit_14->text();
//    QString namee = ui->lineEdit_2->text();
//    QString agee = ui->lineEdit_3->text();
//    QString talll = ui->lineEdit_4->text();
//    QString weightt = ui->lineEdit_5->text();
//    QString poss = ui->lineEdit_6->text();
//    QString test = ui->lineEdit_7->text();

//    if(idd == "" || playeridd == "" || namee == "" || agee == "" || talll == "" || weightt == "" || poss == "")
//    {
//        QMessageBox::warning(this, QString::fromLocal8Bit("更新球员信息"), QString::fromLocal8Bit("不能为空!"), QMessageBox::Yes);
//        ui->lineEdit->clear();
//        ui->lineEdit_14->clear();
//        ui->lineEdit_2->clear();
//        ui->lineEdit_3->clear();
//        ui->lineEdit_4->clear();
//        ui->lineEdit_5->clear();
//        ui->lineEdit_6->clear();
//        ui->lineEdit_7->clear();
//        ui->lineEdit_14->setFocus();
//        return ;
//    }

//    if(test == "qtqtqt")
//    {
//        QSqlQuery qry;
//        qry.prepare( "SELECT * FROM playerinfortable" ); //打开一种操作
//        qry.exec(); //开始执行操作
//        QSqlRecord rec = qry.record();

//        int find_player = 0;
//        for(int r = 0; qry.next(); ++r)
//        {
//            QString nowstring = qry.value(0).toString();
//            if(nowstring == playeridd)
//                find_player =1;
//        }
//        if(!find_player)
//        {
//            QMessageBox::warning(this, QString::fromLocal8Bit("更新球员信息"), QString::fromLocal8Bit("该球员信息未录入"), QMessageBox::Yes);
//            ui->lineEdit->clear();
//            ui->lineEdit_14->clear();
//            ui->lineEdit_2->clear();
//            ui->lineEdit_3->clear();
//            ui->lineEdit_4->clear();
//            ui->lineEdit_5->clear();
//            ui->lineEdit_6->clear();
//            ui->lineEdit_7->clear();
//            ui->lineEdit_14->setFocus();
//            return ;
//        }

//        int find_team = 0;
//        qry.prepare( "SELECT * FROM teaminfortable" ); //打开一种操作
//        qry.exec(); //开始执行操作
//        rec = qry.record();

//        for(int r = 0; qry.next(); ++r)
//        {
//            QString nowteam = qry.value(0).toString();
//            if(nowteam == idd) find_team = 1;
//        }
//        if(!find_team)
//        {
//            QMessageBox::warning(this, QString::fromLocal8Bit("更新球员信息"), QString::fromLocal8Bit("该球队信息未录入\n请先录入球队信息"), QMessageBox::Yes);
//            ui->lineEdit->clear();
//            ui->lineEdit_14->clear();
//            ui->lineEdit_2->clear();
//            ui->lineEdit_3->clear();
//            ui->lineEdit_4->clear();
//            ui->lineEdit_5->clear();
//            ui->lineEdit_6->clear();
//            ui->lineEdit_7->clear();
//            ui->lineEdit_14->setFocus();
//            return ;
//        }

//        qry.prepare("create table if not exists playerinfortable(playerid char(30) unique primary key, id char(30), name char(50), age char(30), tall char(30), weight char(30), pos char(30))");
//        qry.prepare(QString("update playerinfortable set id = '%1', name = '%2', age = '%3', tall = '%4', weight = '%5', pos = '%6' where playerid = '%7' ").arg(idd).arg(namee).arg(agee).arg(talll).arg(weightt).arg(poss).arg(playeridd));
//        if( !qry.exec() )
//            qDebug() << qry.lastError();
//        else
//            qDebug( "Updated!" );

//        QMessageBox::information(this, QString::fromLocal8Bit("更新球员信息"), QString::fromLocal8Bit("更新成功!"), QMessageBox::Yes);
//        ui->lineEdit->clear();
//        ui->lineEdit_14->clear();
//        ui->lineEdit_2->clear();
//        ui->lineEdit_3->clear();
//        ui->lineEdit_4->clear();
//        ui->lineEdit_5->clear();
//        ui->lineEdit_6->clear();
//        ui->lineEdit_7->clear();
//        ui->lineEdit_14->setFocus();
//    }

//    else
//    {
//        QMessageBox::warning(this, QString::fromLocal8Bit("更新球员信息"), QString::fromLocal8Bit("验证密码错误!"), QMessageBox::Yes);
//        ui->lineEdit_7->clear();
//        ui->lineEdit_7->setFocus();
//    }
//}

void TeamOper::on_pushButton_10_clicked() //查看全部球员
{
    openp = 1;
    viewp = new ViewPlayer();
    viewp->open();
}

void TeamOper::on_pushButton_11_clicked() //删除球队
{
    QString teamid = ui->lineEdit_9->text();
    QString test = ui->lineEdit_13->text();

    if(teamid == "")
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("删除球队信息"), QString::fromLocal8Bit("请输入球队名!"), QMessageBox::Yes);
        ui->lineEdit_8->clear();
        ui->lineEdit_9->clear();
        ui->lineEdit_10->clear();
        ui->lineEdit_11->clear();
        ui->lineEdit_12->clear();
        ui->lineEdit_13->clear();
        ui->lineEdit_8->setFocus();
        return ;
    }

    if(test == "qtqtqt")
    {
        QSqlQuery qry;
        qry.prepare( "SELECT * FROM teaminfortable" ); //打开一种操作
        qry.exec(); //开始执行操作
        QSqlRecord rec = qry.record();

        int find_team = 0;
        for(int r = 0; qry.next(); ++r)
        {
            QString nowstring = qry.value(1).toString();
            if(nowstring == teamid)
                find_team = 1;
        }
        if(!find_team)
        {
            QMessageBox::warning(this, QString::fromLocal8Bit("删除球队信息"), QString::fromLocal8Bit("该球队信息未录入"), QMessageBox::Yes);
            ui->lineEdit_8->clear();
            ui->lineEdit_9->clear();
            ui->lineEdit_10->clear();
            ui->lineEdit_11->clear();
            ui->lineEdit_12->clear();
            ui->lineEdit_13->clear();
            ui->lineEdit_8->setFocus();
            return ;
        }

        //已经生成比赛的球队不能删除
        qry.prepare( "SELECT * FROM matchtable" ); //打开一种操作
        qry.exec(); //开始执行操作
        rec = qry.record();
        for(int r = 0; qry.next(); ++r)
        {
            QString nowteam1 = qry.value(1).toString();
            QString nowteam2 = qry.value(2).toString();
            if(nowteam1 == teamid)
            {
                QMessageBox::warning(this, QString::fromLocal8Bit("删除球队信息"), QString::fromLocal8Bit("该球队已参加比赛\n不能删除!"), QMessageBox::Yes);
                ui->lineEdit_8->clear();
                ui->lineEdit_9->clear();
                ui->lineEdit_10->clear();
                ui->lineEdit_11->clear();
                ui->lineEdit_12->clear();
                ui->lineEdit_13->clear();
                ui->lineEdit_8->setFocus();
                return ;
            }
            if(nowteam2 == teamid)
            {
                QMessageBox::warning(this, QString::fromLocal8Bit("删除球队信息"), QString::fromLocal8Bit("该球队已参加比赛\n不能删除!"), QMessageBox::Yes);
                ui->lineEdit_8->clear();
                ui->lineEdit_9->clear();
                ui->lineEdit_10->clear();
                ui->lineEdit_11->clear();
                ui->lineEdit_12->clear();
                ui->lineEdit_13->clear();
                ui->lineEdit_8->setFocus();
                return ;
            }
        }

        qry.prepare(QString("delete from teaminfortable where id = '%1' ").arg(teamid));
        if( !qry.exec() )
            qDebug() << qry.lastError();
        else
            qDebug( "Deleted!" );

        QMessageBox::information(this, QString::fromLocal8Bit("删除球队信息"), QString::fromLocal8Bit("删除成功!"), QMessageBox::Yes);
        ui->lineEdit_8->clear();
        ui->lineEdit_9->clear();
        ui->lineEdit_10->clear();
        ui->lineEdit_11->clear();
        ui->lineEdit_12->clear();
        ui->lineEdit_13->clear();
        ui->lineEdit_8->setFocus();

//        int findd = 1;
//        while(findd)
//        {
//            findd = 0;
//            qry.prepare( "SELECT * FROM matchtable" ); //打开一种操作
//            qry.exec(); //开始执行操作
//            rec = qry.record();
//            for(int r = 0; qry.next(); ++r)
//            {
//                QString nowteam1 = qry.value(1).toString();
//                QString nowteam2 = qry.value(2).toString();
//                if(nowteam1 == teamid)
//                {
//                    int digi = qry.value(0).toInt();
//                    qry.prepare(QString("delete from matchtable where digitime = %1 ").arg(digi));
//                    if( !qry.exec() )
//                        qDebug() << qry.lastError();
//                    else
//                        qDebug( "Deleted! team1" );
//                    findd = 1;
//                }
//                if(nowteam2 == teamid)
//                {
//                    int digi = qry.value(0).toInt();
//                    qry.prepare(QString("delete from matchtable where team2 = '%1' ").arg(teamid));
//                    if( !qry.exec() )
//                        qDebug() << qry.lastError();
//                    else
//                        qDebug( "Deleted! team2" );
//                    findd = 1;
//                }
//            }
//        }
    }

    else
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("删除球队信息"), QString::fromLocal8Bit("验证密码错误!"), QMessageBox::Yes);
        ui->lineEdit_7->clear();
        ui->lineEdit_13->setFocus();
    }
}

void TeamOper::on_pushButton_12_clicked() //查看全部球队
{
    opent = 1;
    viewt = new ViewTeam();
    viewt->open();
}
