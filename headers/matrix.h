#include "vector.h"
#ifndef MATRIX_H // Include guard
#define MATRIX_H
class matrix
{
public:
    double get(int colId, int rowId) {}
    void set(int colId, int rowId, double value) {}
    matrix multiply_left(matrix *other) {}
    matrix multiply_right(matrix *other) {}
    matrix add(matrix *other) {}
    matrix substract(matrix *other) {}
    matrix inverse() {}
    vector mul_by_vec_left(vector *other) {}
    vector mul_by_vec_right(vector *other) {}
    vector eigenvalues() {} // todo
    double get_determinant() {}
    matrix transpose() {}
    double frob_norm() {}
    matrix scale(double by) {}
    void print() {}
    matrix(int col, int rows_, int gap_ = 1) {}
    ~matrix() {}
};
#endif