#ifndef EXEPTION_H
#define EXEPTION_H
#include <iostream>
#include <QString>
using namespace std;

class BasicQueueException : public std::logic_error {
public:
    explicit BasicQueueException(const char* message):std::logic_error(message) {}
};
#endif // EXEPTION_H
