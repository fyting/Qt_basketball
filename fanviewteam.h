#ifndef FANVIEWTEAM_H
#define FANVIEWTEAM_H

#include <QDialog>

namespace Ui {
class FanViewTeam;
}

class FanViewTeam : public QDialog
{
    Q_OBJECT

public:
    explicit FanViewTeam(QWidget *parent = 0);
    ~FanViewTeam();

private:
    Ui::FanViewTeam *ui;
};

#endif // FANVIEWTEAM_H
