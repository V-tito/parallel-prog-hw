#include <stdlib.h>
#include <iostream>
#include "..\headers\vector.h"
class vector
{
private:
    double *self;
    int size;

public:
    double get(int id) {}
    void set(int id, double value) {}
    int getSize() {}
    void print() {}
    vector(int size_) {}
    ~vector() {}
};
void vector::print()
{
    for (int j = 0; j < this->size; j++)
    {
        std::cout << this->get(j);
    }
    std::cout << "\n";
}
double vector::get(int id)
{
    double *ptr = this->self + id;
    return *ptr;
}
void vector::set(int id, double value)
{
    double *ptr = this->self + id;
    *ptr = value;
}
int vector::getSize()
{
    return this->size;
}
vector::vector(int size_)
{
    self = (double *)malloc(size_ * (sizeof(double)));
    size = size_;
}
vector::~vector() { free(self); }