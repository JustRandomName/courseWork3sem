#ifndef PERSON_H
#define PERSON_H

#include <QDialog>
#include <vector>
#include <QDebug>
namespace Ui {
class Person;
}

class Person : public QDialog
{
    Q_OBJECT

public:
    explicit Person(QWidget *parent = 0);
    explicit Person(const Person& obj);
    ~Person();
    bool flag = true;
    QString name;
    QString dok;
    QString diag;
    std::vector <Person> write;
    Person& operator=(const Person &obj);
private slots:
    void on_Name_textEdited(const QString &arg1);

    void on_psss_or_diag_textEdited(const QString &arg1);

    void on_pushButton_clicked();
private:
    Ui::Person *ui;
};

#endif // PERSON_H
