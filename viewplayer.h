#ifndef VIEWPLAYER_H
#define VIEWPLAYER_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class ViewPlayer;
}

class ViewPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit ViewPlayer(QWidget *parent = 0);
    ~ViewPlayer();

private slots:
    void update();

private:
    Ui::ViewPlayer *ui;
    QSqlTableModel *model;
};

#endif // VIEWPLAYER_H
