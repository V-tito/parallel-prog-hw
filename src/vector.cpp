#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "../headers/vector.h"
#include <cstring>
#include<cmath>

vector::vector(const vector &other) : size(other.size)
{
    this->self = (double *)malloc(size * sizeof(double));
    memcpy(self, other.self, size * sizeof(double));
}
void vector::print()
{
    for (int j = 0; j < this->size; j++)
    {
        std::cout << this->get(j)<<"\n";
    }
    std::cout << "\n";
}
void vector::fprint(std::ofstream& of)
{
    for (int j = 0; j < this->size; j++)
    {
        of << this->get(j)<<"\n";
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
vector vector::scale(double by){
    vector res=vector(this->size);
    for (int i=0;i<this->size;i++){
        res.set(i,this->get(i)*by);}
    return res;
}
double vector::eucledianNorm(){
    double res=0;
    for (int i=0;i<this->size;i++){
        res+=pow(this->get(i),2);
    }
    res=sqrt(res);
    return res;

}
vector::vector(int size_)
{
    self = (double *)malloc(size_ * (sizeof(double)));
    size = size_;
}
vector::~vector() { free(self); }

vector vector::add(vector *other){
    if (this->size==other->size) {
        vector res=vector(this->size);
        for (int i=0;i<this->size;i++){
            res.set(i,this->get(i)+other->get(i));
        }
        return res;
    } else {
        throw std::invalid_argument("sizes do not match!");
    }
}
    double vector::scalar_mul_left(vector*other){
        if (this->size==other->size) {
        double res=0;
        for (int i=0;i<this->size;i++){
            res+=this->get(i)*other->get(i);
        }
        return res;
    } else {
        throw std::invalid_argument("sizes do not match!");
    }
    }