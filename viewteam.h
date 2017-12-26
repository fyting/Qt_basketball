#ifndef VIEWTEAM_H
#define VIEWTEAM_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class ViewTeam;
}

class ViewTeam : public QDialog
{
    Q_OBJECT

public:
    explicit ViewTeam(QWidget *parent = 0);
    ~ViewTeam();

private slots:
    void update();

private:
    Ui::ViewTeam *ui;
    QSqlTableModel *model;
};

#endif // VIEWTEAM_H
