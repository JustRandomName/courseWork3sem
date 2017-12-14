#include "entity.h"
#include "ui_entity.h"

Entity::Entity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Entity)
{
    ui->setupUi(this);
}

Entity::~Entity()
{
    delete ui;
}
