#ifndef FANLOGIN_H
#define FANLOGIN_H

#include <QDialog>

namespace Ui {
class fanlogin;
}

class fanlogin : public QDialog
{
    Q_OBJECT

public:
    explicit fanlogin(QWidget *parent = 0);
    ~fanlogin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::fanlogin *ui;
};

#endif // FANLOGIN_H
