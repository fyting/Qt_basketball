#ifndef TEAMREGISTER_H
#define TEAMREGISTER_H

#include <QDialog>

namespace Ui {
class TeamRegister;
}

class TeamRegister : public QDialog
{
    Q_OBJECT

public:
    explicit TeamRegister(QWidget *parent = 0);
    ~TeamRegister();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::TeamRegister *ui;
};

#endif // TEAMREGISTER_H
