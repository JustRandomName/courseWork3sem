#ifndef ENTITY_H
#define ENTITY_H

#include <QDialog>

namespace Ui {
class Entity;
}

class Entity : public QDialog
{
    Q_OBJECT

public:
    explicit Entity(QWidget *parent = 0);
    explicit Entity(const Entity& obj);
    ~Entity();
    int size;
    QString name;
    QString dok;
    QString diag;
    Entity& operator=(const Entity &obj);
    std::vector <Entity> write;

private:
    Ui::Entity *ui;
};

#endif // ENTITY_H
