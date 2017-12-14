#ifndef EXEPTION_H
#define EXEPTION_H
#include <iostream>
#include <QString>
using namespace std;

class ExeptionAbstract : public std::logic_error {
public:
    explicit ExeptionAbstract(const char* message):std::logic_error(message) {}
};
#endif // EXEPTION_H
