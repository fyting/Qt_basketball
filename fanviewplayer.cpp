#include "fanviewplayer.h"
#include "ui_fanviewplayer.h"
#include <QMessageBox>
#include <QDebug>
#include <QtSql>

extern QString teamid;

FanViewPlayer::FanViewPlayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FanViewPlayer)
{
    ui->setupUi(this);
    this->setFixedSize(500, 309);
    setWindowTitle(QString::fromLocal8Bit("查看该队球员信息"));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("D:\\VS+QT\\practice\\basketball\\basketball.db");

    if(!db.open())
    {
      qDebug() << db.lastError();
      qFatal("Failed to connect.");
    }
    qDebug("Connected!");

    playermodel = new QSqlTableModel(this);
    playermodel->setTable("playerinfortable");
    playermodel->select();
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->setModel(playermodel);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setColumnWidth(0,53);
    ui->tableView->setColumnWidth(1,60);
    ui->tableView->setColumnWidth(2,70);
    ui->tableView->setColumnWidth(3,60);
    ui->tableView->setColumnWidth(4,60);
    ui->tableView->setColumnWidth(5,60);
    ui->tableView->setColumnWidth(6,70);

    QSqlQuery qry;
    qry.prepare( "SELECT * FROM playerinfortable" ); //打开一种操作
    qry.exec(); //开始执行操作
    QSqlRecord rec = qry.record();

    for(int r = 0; qry.next(); ++r)
    {
        QString nowid = qry.value(1).toString();
        if(nowid != teamid)
        {qDebug() << nowid << teamid;
            ui->tableView->setRowHidden(r,1);
        }
    }
}

FanViewPlayer::~FanViewPlayer()
{
    delete ui;
}
