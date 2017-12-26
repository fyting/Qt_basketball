#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fanlogin.h"
#include "teamlogin.h"
#include "manlogin.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(700, 433);
    setWindowTitle(QString::fromLocal8Bit("篮球比赛管理系统"));
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_2_clicked()
{
    this->close();
    fanlogin fan;
    fan.exec();
    this->show();
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
    TeamLogin team;
    team.exec();
    this->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    this->close();
    ManLogin man;
    man.exec();
    this->show();
}
