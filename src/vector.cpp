#include <stdlib.h>
class vector
{
private:
    double *self;
    int size;

public:
    double get(int id) {}
    void set(int id, double value) {}
    int getSize() {}
    vector(int size_) {}
    ~vector() {}
};

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