#ifndef MANLOGIN_H
#define MANLOGIN_H

#include <QDialog>

namespace Ui {
class ManLogin;
}

class ManLogin : public QDialog
{
    Q_OBJECT

public:
    explicit ManLogin(QWidget *parent = 0);
    ~ManLogin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ManLogin *ui;
};

#endif // MANLOGIN_H
