#ifndef ADD_PAT_H
#define ADD_PAT_H

#include <QDialog>
#include <vector>
namespace Ui {
class add_pat;
}

class add_pat : public QDialog
{
    Q_OBJECT

public:
    explicit add_pat(QWidget *parent = 0);
    explicit add_pat(const add_pat& obj);
    ~add_pat();
    int size;
    QString name;
    QString dok;
    QString diag;
    add_pat& operator=(const add_pat &obj);
    std::vector <add_pat> write;
private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::add_pat *ui;
};




#endif // ADD_PAT_H
