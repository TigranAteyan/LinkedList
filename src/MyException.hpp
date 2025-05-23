#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <exception>

class MyException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid input!";
    }
};

#endif