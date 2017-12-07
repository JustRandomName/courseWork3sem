#ifndef BASE_H
#define BASE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QWidget>
#include "add_pat.h"
#include <expt.h>
namespace Ui {
class Base;
}

class Base : public QDialog
{
    Q_OBJECT

public:
    explicit Base(QWidget *parent = 0, QString _username = "null", QString _role = "null");
    ~Base();
    void deleteQuere(QString tableName, QString deleteEntity, QString row);
    void loadDB(QString way, QString name_BD);
    void writeOnLog(QString data);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_tableView_activated(const QModelIndex &index);
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();

private:
    bool flag = false;
    bool verification = false;
    QString username;
    QString role;
    add_pat* add;
    Ui::Base *ui;
    QSqlTableModel* model;
    QSqlDatabase BD;
    QString generateUserId();
};

#endif // BASE_H
