#include <math.h>

class matrix
{
private:
    int columns;
    int rows;
    int gap;
    long determinant;
public:
    long multiply_left (matrix other){} 
    long multiply_right(matrix other){}
    long get_determinant(){}
    matrix transpose(){}
    matrix scale(long by) {}
    matrix(/* args */);
    ~matrix();
};

matrix::matrix(/* args */)
{
}

matrix::~matrix()
{
}
