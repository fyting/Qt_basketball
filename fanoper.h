#ifndef FANOPER_H
#define FANOPER_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class FanOper;
}

class FanOper : public QDialog
{
    Q_OBJECT

public:
    explicit FanOper(QWidget *parent = 0);
    ~FanOper();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_tableView_5_clicked(const QModelIndex &index);

    void on_pushButton_7_clicked();

    void on_tableView_6_clicked(const QModelIndex &index);

private:
    Ui::FanOper *ui;
    QSqlTableModel *scoremodel;
    QSqlTableModel *ticketmodel;
};

#endif // FANOPER_H
