#ifndef FANREGISTER_H
#define FANREGISTER_H

#include <QDialog>

namespace Ui {
class FanRegister;
}

class FanRegister : public QDialog
{
    Q_OBJECT

public:
    explicit FanRegister(QWidget *parent = 0);
    ~FanRegister();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::FanRegister *ui;
};

#endif // FANREGISTER_H
