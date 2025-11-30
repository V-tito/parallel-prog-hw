#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "../headers/vector.h"

void vector::print()
{
    for (int j = 0; j < this->size; j++)
    {
        std::cout << this->get(j);
    }
    std::cout << "\n";
}
void vector::fprint(std::ofstream& of)
{
    for (int j = 0; j < this->size; j++)
    {
        of << this->get(j);
    }
    of << "\n";
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