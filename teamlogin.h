#ifndef TEAMLOGIN_H
#define TEAMLOGIN_H

#include <QDialog>

namespace Ui {
class TeamLogin;
}

class TeamLogin : public QDialog
{
    Q_OBJECT

public:
    explicit TeamLogin(QWidget *parent = 0);
    ~TeamLogin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::TeamLogin *ui;
};

#endif // TEAMLOGIN_H
