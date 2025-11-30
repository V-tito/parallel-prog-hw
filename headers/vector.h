#include <iostream>
#include <fstream>

#ifndef VECTOR_H // Include guard
#define VECTOR_H
class vector
{
    private:
    double *self;
    int size;

public:
    double get(int id) ;
    void set(int id, double value) ;
    int getSize() ;
    void print() ;
    void fprint(std::ofstream& of);
    vector(int size_) ;
    ~vector() ;
};
#endif