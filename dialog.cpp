#include "dialog.h"
#include "ui_dialog.h"

using namespace std;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog() {
    delete ui;
}


void Dialog::on_pushButton_clicked() {
    close();
}

void Dialog::on_pushButton_2_clicked() { // обернуть в свой try
    QSqlDatabase DB = QSqlDatabase :: addDatabase("QSQLITE");
    DB = QSqlDatabase :: addDatabase("QSQLITE");
    DB.setDatabaseName("D:\\DataBase.db");
    if(!DB.open()) exit(1);
    QSqlQuery query1;
    QSqlQuery query;
    query1.exec("SELECT role FROM secretData WHERE userId = \'" + usver_ID +"\' AND password = \'" + userPassword + "\';");
    query.exec("SELECT username FROM doktors WHERE userId = \'" + usver_ID + "\';");
    query1.first();
    query.first();
    role = query1.value(0).toString();
    username = query.value(0).toString();
    if(role == "" || username == "") {
        this->~Dialog();
        Dialog* dialog = new Dialog();
        dialog->exec();
    } else {
        Base* base = new Base(0, username, role);
        base->writeOnLog("\nUser " + username + " enter in system whith role " + role + ";");
        base->exec();
    }

}

void Dialog::on_lineEdit_textEdited(const QString &arg1) {
    usver_ID = arg1;
    if(usver_ID.isEmpty())
        ui->pushButton_2->setEnabled(false);
    else ui->pushButton_2->setEnabled(true);
}

void Dialog::on_lineEdit_2_textEdited(const QString &arg1) {
    userPassword = arg1;
    if(userPassword.isEmpty())
        ui->pushButton_2->setEnabled(false);
}
