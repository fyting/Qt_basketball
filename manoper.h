#ifndef MANOPER_H
#define MANOPER_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class ManOper;
}

class ManOper : public QDialog
{
    Q_OBJECT

public:
    explicit ManOper(QWidget *parent = 0);
    ~ManOper();
    void insert_score_table(QString, QString, QString, QString);
    void update_score_table(QString, QString, QString, QString, QString, QString);
    void update_ticket(QString, QString, QString, QString, QString, QString);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

//    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_15_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_tableView_3_clicked(const QModelIndex &index);

    void on_pushButton_17_clicked();

    void on_pushButton_19_clicked();

    void on_tableView_4_clicked(const QModelIndex &index);

    void on_pushButton_18_clicked();

    void on_tableView_5_clicked(const QModelIndex &index);

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_tableView_6_clicked(const QModelIndex &index);

private:
    Ui::ManOper *ui;
    QSqlTableModel *team1model;
    QSqlTableModel *team2model;
    QSqlTableModel *gymmodel;
    QSqlTableModel *matchmodel;
    QSqlTableModel *scoremodel;
    QSqlTableModel *ticketmodel;
};

#endif // MANOPER_H
