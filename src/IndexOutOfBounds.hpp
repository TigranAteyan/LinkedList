#ifndef INDEXOUTOFBOUNDS_H
#define INDEXOUTOFBOUNDS_H
#include <exception>

class IndexOutOfBounds : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid input!";
    }
};

#endif
