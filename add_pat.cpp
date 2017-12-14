
#include <QString>
#include <vector>
#include <QDebug>
#include "Entity.h"

Entity::Entity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Entity)
{

    ui->setupUi(this);
}

Entity::Entity(const Entity& obj){
    name = obj.name;
    dok = obj.dok;
    diag = obj.diag;
}

Entity::~Entity() {
    delete ui;
}


void Entity::on_lineEdit_textChanged(const QString &arg1) {
   name = arg1;
}

void Entity::on_lineEdit_2_textEdited(const QString &arg1) {
    diag = arg1;
}



void Entity::on_pushButton_clicked() {
    write.push_back(Entity(*this));
    close();

}
