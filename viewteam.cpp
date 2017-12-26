#include "viewteam.h"
#include "ui_viewteam.h"
#include <QtSql>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>

ViewTeam::ViewTeam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewTeam)
{
    ui->setupUi(this);
    this->setFixedSize(500, 309);
    setWindowTitle(QString::fromLocal8Bit("查看全部球队"));

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("D:\\VS+QT\\practice\\basketball\\basketball.db");

    if(!db.open())
    {
      qDebug() << db.lastError();
      qFatal("Failed to connect.");
    }
    qDebug("Connected!");

    QTimer *timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(600);

    model  = new QSqlTableModel(this);
    model->setTable("teaminfortable");
    model->select();
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->setModel(model);
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);

    ui->tableView->setColumnWidth(0,49);
    ui->tableView->setColumnWidth(1,85);
    ui->tableView->setColumnWidth(2,125);
    ui->tableView->setColumnWidth(3,80);
    ui->tableView->setColumnWidth(4,80);
}

ViewTeam::~ViewTeam()
{
    delete ui;
}

void ViewTeam::update()
{
    model  = new QSqlTableModel(this);
    model->setTable("teaminfortable");
    model->select();
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->setModel(model);
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);
}
