#include <iostream>
#include <fstream>
#include <cstring>

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
    double eucledianNorm();
    vector scale(double by);
    vector add(vector *other);
    double scalar_mul_left(vector*other);
    vector(const vector &other);
    vector &operator=(const vector &other)
    {
        if (this != &other)
        {
            free(self); // Release old memory
            size=other.size;
            self = (double *)malloc(size * sizeof(double));
            std::memcpy(self, other.self, size * sizeof(double));
        }
        return *this;
    };
    vector(int size_) ;
    ~vector() ;
};
#endif