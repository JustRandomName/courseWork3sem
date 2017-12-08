#include "ui_add_pat.h"
#include "add_pat.h"

add_pat::add_pat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_pat)
{

    ui->setupUi(this);
}

add_pat::add_pat(const add_pat& obj){
    name = obj.name;
    dok = obj.dok;
    diag = obj.diag;
}

add_pat::~add_pat() {
    delete ui;
}


void add_pat::on_lineEdit_textChanged(const QString &arg1) {
   name = arg1;
}

void add_pat::on_lineEdit_2_textEdited(const QString &arg1) {
    diag = arg1;
}



void add_pat::on_pushButton_clicked() {
    write.push_back(add_pat(*this));
    close();

}
