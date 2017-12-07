#include "base.h"
#include "ui_base.h"
#include "add_pat.h"
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
    else {
        throw EmptyQueueException();
    }
}

QString Base :: generateUserId() {
    char tokenArr[] = {'1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','k','l','m','n'}; // size = 21
    QString generetedId;
    srand(time(NULL));
    for(int i = 0; i < 8; i++)
        generetedId += tokenArr[rand()%21];
    return generetedId;
}

void Base :: deleteQuere(QString tableName, QString deleteEntity, QString row) {     // удаление по username
    add = new add_pat();
    add->exec();
    BD = QSqlDatabase :: addDatabase("QSQLITE");
    BD.setHostName("127.0.0.1");
    BD.setUserName("SYSDBA");
    BD.setPassword("masterkey");
    BD.setDatabaseName("D:\\DataBase.db");
    BD.open();
    qDebug() << "DELETE FROM \'" + tableName + "\' WHERE \'" + row +"\' = \'" + add->write[0].name +"\';";
    QSqlQuery query = BD.exec("DELETE FROM \'" + tableName + "\' WHERE " + row + " = \'" + add->write[0].name +"\';"); // try
    writeOnLog(" User " + username + " delete " + deleteEntity + " " + add->write[0].name + " from database; ");
    model->select();
    ui->tableView->setModel(model);
    BD.close();

}

void Base::loadDB(QString way, QString name_BD) {
    if(verification){
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
    }

    BD = QSqlDatabase :: addDatabase("QSQLITE");
    BD.setHostName("127.0.0.1");
    BD.setUserName("SYSDBA");
    BD.setPassword("masterkey");
    BD.setDatabaseName(way);
    if(!BD.open()) throw EmptyQueueException();

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

    ui->tableView->setModel(model);
    ui->comboBox->setModel(model);
    ui->comboBox->setModelColumn(0);
    BD.close();
}

Base::~Base() {
    delete ui;
}

void Base::on_pushButton_clicked() {
    this->~Base();
}

void Base::on_pushButton_2_clicked() {
    flag = false;
    verification = true;
    loadDB("D:\\DataBase.db", "patient");
}


void Base::on_tableView_activated(const QModelIndex &index) { }

void Base::on_pushButton_3_clicked() {
    flag = true;
    if(QString :: compare(role, "admin") == 0)
        verification = true;
    else
        verification = false;
    try {
        loadDB("D:\\DataBase.db", "dok_log");
    } catch (EmptyQueueException& e) {
        writeOnLog(e.what());
    }
}

void Base::on_pushButton_5_clicked() {  // название таблицы, 3 значения
    add = new add_pat();
    add->exec();
    BD = QSqlDatabase :: addDatabase("QSQLITE");
    BD.setDatabaseName("D:\\DataBase.db");
    try {
        BD.open();
    } catch(...) {
        qDebug()<< "DB";
    }
    QSqlQuery query;
    if(flag == true) {
        for(size_t i = 0; i < add->write.size(); i++) {
            QString _userId = generateUserId();
            query.prepare("INSERT INTO dok_log (userId, username) VALUES (\'"+ _userId +"\',\'"+ add->write[i].name +"\')");
            QSqlQuery query1;
            query1.prepare("INSERT INTO secretdata (userId, password, role) VALUES(\'"+ _userId +"\',\'"+ add->write[i].diag +"\', 'user' )");
            writeOnLog("User " + username + " add to system doctor " + add->write[i].name + " whith password " + add->write[i].diag + ";");
        }
    } else {
        for(size_t i = 0; i < add->write.size(); i++){
            query.prepare("INSERT INTO patient (diag, name, doctor) VALUES (\'"+ add->write[i].diag +"\','"+ add->write[i].name +"\','"+ username +"\')");
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
        deleteQuere("dok_log", "doctor", "username");
    else
        deleteQuere("patient", "patient", "name");
}
