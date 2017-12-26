#ifndef TEAMOPER_H
#define TEAMOPER_H

#include "viewplayer.h"
#include "viewteam.h"
#include <QDialog>

namespace Ui {
class TeamOper;
}

class TeamOper : public QDialog
{
    Q_OBJECT

public:
    explicit TeamOper(QWidget *parent = 0);
    ~TeamOper();

private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_clicked();

//    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_9_clicked();

//    void on_pushButton_4_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::TeamOper *ui;
    ViewPlayer *viewp;
    ViewTeam *viewt;
};

#endif // TEAMOPER_H
