#include "base.h"
#include "ui_base.h"
#include "person.h"
#include <QtSql>
#include <QWidget>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QString>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>


Base::Base(QWidget *parent, QString _username, QString _role) :
    QDialog(parent),
    ui(new Ui::Base)
{
    role = _role;
    username = _username;
    ui->setupUi(this);

}

void Base :: writeOnLog(QString data) {
    QFile file ("D:/log/file1.txt");
    if(file.open( QIODevice :: Append )) {
        QTextStream textStream(&file);
        textStream << "\r\n";
        textStream << data;
        file.close();
        return;
    }
    else throw EmptyExeption();

}

QString Base :: generateUserId() {
    char tokenArr[] = {'1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','k','l','m','n'}; // size = 21
    QString generetedId;
    srand(time(NULL));
    for(int i = 0; i < 8; i++)
        generetedId += tokenArr[rand()%21];
    return generetedId;
}

void Base :: deleteQuere(QString tableName, QString deleteEntity, QString row) {
    add = new Person();
    add->exec();

    if(add->flag) {
        loadDB("D:\\DataBase.db", tableName);
    } else{
        BD = QSqlDatabase :: addDatabase("QSQLITE");
        BD.setDatabaseName("D:\\DataBase.db");
        BD.open();
        qDebug() << "DELETE FROM \'" + tableName + "\' WHERE \'" + row +"\' = \'" + add->write[0].name +"\';";
        QSqlQuery query = BD.exec("DELETE FROM \'" + tableName + "\' WHERE " + row + " = \'" + add->write[0].name +"\';"); // try
        if(tableName.compare("doctors")) {
            QSqlQuery query1 = BD.exec("DELETE FROM secretdata WHERE userId = \'" + add->write[0].diag + "\';");
            qDebug()<<"DELETE FROM secretdata WHERE userId = \'" + add->write[0].diag + "\';";
        }
        writeOnLog(" User " + username + " delete " + deleteEntity + " " + add->write[0].name + " from database; ");
        model->select();
        ui->tableView->setModel(model);
        BD.close();
    }
}

void Base::loadDB(QString way, QString name_BD) {
    if(verification){
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
    }

    BD = QSqlDatabase :: addDatabase("QSQLITE");

    BD.setDatabaseName(way);
    if(!BD.open()) throw EmptyExeption();

    model = new QSqlTableModel(this, BD);
    model->setTable(name_BD);

    if(QString :: compare("admin", role) == 0){
        model->select();
    } else {
        if(QString :: compare("user", role) == 0) {
            model->select();
            model->setFilter("doctor = \'" + username +"\'");
        } else
            model->select();
    }
    ui->tableView->setEnabled(true);
    ui->tableView->setModel(model);
    ui->tableView->colorCount();
    BD.close();
}

Base::~Base() {
    delete ui;
}

void Base::on_pushButton_clicked() {
    close();
}

void Base::on_pushButton_2_clicked() {
    flag = false;
    verification = true;
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
    loadDB("D:\\DataBase.db", "patient");
}


void Base::on_tableView_activated(const QModelIndex &index) { }

void Base::on_pushButton_3_clicked() {
    flag = true;
    if(QString :: compare(role, "admin") == 0)
        verification = true;
    else {
        verification = false;
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
    }
    try {
        loadDB("D:\\DataBase.db", "doktors");
    } catch (EmptyExeption& e) {
        writeOnLog(e.what());
    }
}

void Base::on_pushButton_5_clicked() {  // название таблицы, 3 значения
    add = new Person();
    add->exec();
    BD = QSqlDatabase :: addDatabase("QSQLITE");
    BD.setDatabaseName("D:\\DataBase.db");
    try {
        BD.open();
    } catch(...) {
        exit(1);
    }
    QSqlQuery query;
    if(flag == true) {
        for(size_t i = 0; i < add->write.size(); i++) {
            QString _userId = generateUserId();
            query.prepare("INSERT INTO doktors (userId, username) VALUES (\'"+ _userId +"\',\'"+ add->write[i].name +"\');");
            QSqlQuery query1;
            qDebug() << _userId;
            qDebug() << add->write[i].diag;

            bool fl = query1.exec("INSERT INTO secretdata (userId, password, role) VALUES(\'"+ _userId +"\',\'"+ add->write[i].diag +"\', 'user' );");
            qDebug() << fl;
            writeOnLog("User " + username + " add to system doctor " + add->write[i].name + " whith password " + add->write[i].diag + ";");
        }
    } else {
        for(size_t i = 0; i < add->write.size(); i++) {
            query.prepare("INSERT INTO patient (diag, name, doctor) VALUES (\'"+ add->write[i].diag +"\','"+ add->write[i].name +"\','"+ username +"\');");
            writeOnLog("User " + username + " add to system patient " + add->write[i].name + " whith diagnosis " + add->write[i].diag + ";");
        }
    }
    query.exec();
    model->select();
    ui->tableView->setModel(model);
    add->write.clear();
    BD.close();
}



void Base::on_pushButton_4_clicked() {
    if(flag)
        deleteQuere("doktors", "doctor", "username");
    else
        deleteQuere("patient", "patient", "name");
}
