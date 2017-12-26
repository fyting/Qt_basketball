#ifndef FANVIEWPLAYER_H
#define FANVIEWPLAYER_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class FanViewPlayer;
}

class FanViewPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit FanViewPlayer(QWidget *parent = 0);
    ~FanViewPlayer();

private:
    Ui::FanViewPlayer *ui;
    QSqlTableModel *playermodel;
};

#endif // FANVIEWPLAYER_H
