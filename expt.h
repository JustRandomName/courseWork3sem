#ifndef EXPT_H
#define EXPT_H
#include "ExeptionAbstract.h"
#include <iostream>
#include <QString>
using namespace std;

class EmptyExeption : public ExeptionAbstract {
public:
    explicit EmptyExeption() : ExeptionAbstract("Queue is empty") {}
};
#endif // EXPT_H
