#ifndef DIALOG_H
#define DIALOG_H
#include <QtSql>
#include <QDialog>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>
#include "base.h"
// рабочая версия
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

private:
    Ui::Dialog *ui;
    QString usver_ID;
    QString userPassword;
    QString username;
    QString role;
};

#endif // DIALOG_H
