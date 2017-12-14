#include "person.h"
#include "ui_person.h"


Person::Person(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Person)
{
    ui->setupUi(this);
}

Person::Person(const Person &obj) {
    name = obj.name;
    //dok = obj.dok;
    diag = obj.diag;
}

Person::~Person() {
    delete ui;
}

void Person::on_Name_textEdited(const QString &arg1) {
    name = arg1;
    qDebug () << name;
}

void Person::on_psss_or_diag_textEdited(const QString &arg1) {
    diag = arg1;
    qDebug() << diag;
}

void Person::on_pushButton_clicked() {
    if(name.isEmpty() || diag.isEmpty())
        close();
    else {
        flag = false;
        write.push_back(Person(*this));
        qDebug() << write[0].name;
        close();
    }
}
