#ifndef EXPT_H
#define EXPT_H
#include "ExeptionAbstract.h"
#include <iostream>
#include <QString>
using namespace std;

class EmptyQueueException : public BasicQueueException {
public:
    explicit EmptyQueueException() : BasicQueueException("Queue is empty") {}
};
#endif // EXPT_H
