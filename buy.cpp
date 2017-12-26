#include "buy.h"
#include "ui_buy.h"

extern QString money;

Buy::Buy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Buy)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromLocal8Bit("购买球票"));

    ui->lineEdit->setText(money);
}

Buy::~Buy()
{
    delete ui;
}
