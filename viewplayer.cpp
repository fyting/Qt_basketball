#include "viewplayer.h"
#include "ui_viewplayer.h"
#include <QtSql>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>

ViewPlayer::ViewPlayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewPlayer)
{
    ui->setupUi(this);
    this->setFixedSize(500, 309);
    setWindowTitle(QString::fromLocal8Bit("查看全部球员"));

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
    model->setTable("playerinfortable");
    model->select();
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->setModel(model);
    ui->tableView->sortByColumn(1, Qt::AscendingOrder);

    ui->tableView->setColumnWidth(0,51);
    ui->tableView->setColumnWidth(1,58);
    ui->tableView->setColumnWidth(2,68);
    ui->tableView->setColumnWidth(3,58);
    ui->tableView->setColumnWidth(4,58);
    ui->tableView->setColumnWidth(5,58);
    ui->tableView->setColumnWidth(6,68);
}

ViewPlayer::~ViewPlayer()
{
    delete ui;
}

void ViewPlayer::update()
{
    model  = new QSqlTableModel(this);
    model->setTable("playerinfortable");
    model->select();
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->setModel(model);
    ui->tableView->sortByColumn(1, Qt::AscendingOrder);
}
