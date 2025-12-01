#include <omp.h>
#include <stdlib.h>
#include <algorithm>
#include <stdexcept>
#include "../headers/matrix.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>

void matrix::swapRows(int row1, int row2)
{
    double temp;
    for (int i = 0; i < this->columns; i++)
    {
        temp = this->get(i, row1);
        this->set(i, row1, this->get(i, row2));
        this->set(i, row2, temp);
    }}

matrix::matrix(const matrix &other) : rows(other.rows), columns(other.columns), gap(other.gap)
{
    this->self = (double *)malloc((rows + gap) * columns * sizeof(double));
    memcpy(self, other.self, (rows + gap) * columns * sizeof(double));
}
/// @brief вывод в консоль
void matrix::print()
{
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            std::cout << this->get(j, i)<<" | ";
        }
        std::cout << "\n";
    }
}
/// @brief вывод в файл
/// @param of выходной файл
void matrix::fprint(std::ofstream& of)
{
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            of << this->get(j, i)<<" | ";
        }
        of << "\n";
    }
}
double matrix::get(int colId, int rowId)
{
    double *ptr = this->self + (colId * (this->rows + this->gap) + rowId);
    return *ptr;
}

void matrix::set(int colId, int rowId, double value)
{
    double *ptr = this->self + (colId * (this->rows + this->gap) + rowId);
    *ptr = value;
}

matrix::matrix(int col, int rows_, int gap_)
{
    size = col * (rows_ + gap_);
    self = (double *)malloc(size * (sizeof(double)));
    columns = col;
    rows = rows_;
    gap = gap_;
}

matrix::~matrix()
{
    free(self);
}

double matrix::frob_norm()
{
    int n = this->columns;
    int m = this->rows;
    double res = 0;
    double temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            temp = this->get(i, j);
            res += temp * temp;
        }
    }
    res = std::sqrt(res);
    return res;
}
matrix matrix::multiply(matrix *left, matrix *right)
{
    int gap_ = std::max(left->gap, right->gap);
    matrix res = matrix(right->columns, left->rows, gap_);
#pragma omp parallel for num_threads(4)
    for (int i = 0; i < right->columns; i++)
    {
        for (int j = 0; j < left->rows; j++)
        {
            res.set(i, j, 0);
        }
    }
#pragma omp parallel for num_threads(4)
    for (int j = 0; j < right->columns; j++)
    {
        #pragma omp parallel for num_threads(4)
        for (int i = 0; i < left->rows; i++)
        {
            double t;
            t = 0;
            for (int k = 0; k < left->columns; k++)
            {
                    t += left->get(k, i) * right->get(j, k);
                }
            res.set(j, i, t);
        }
    }
    return res;
}

/// Умножить данную матрицу на другую, где матрица, от которой вызывается метод, стоит слева, а аргумент, передваемый в скобках - справа.
/// Возвращает результирующую матрицу.
matrix matrix::multiply_left(matrix *other)
{
    if ((this->columns) == (other->rows))
    {
        matrix res = multiply(this, other);
        return res;
    }
    else
    {
        throw std::invalid_argument("Matrix dimensions do not match!");
    }
}

/// Умножить данную матрицу на другую, где матрица, от которой вызывается метод, стоит справа, а аргумент, передваемый в скобках - слева.
/// Возвращает результирующую матрицу.
matrix matrix::multiply_right(matrix *other)
{
    if ((this->columns) == (other->rows))
    {
        matrix res = multiply(other, this);
        return res;
    }
    else
    {
        throw std::invalid_argument("Matrix dimensions do not match!");
    }
}

matrix matrix::add(matrix *other)
{
    if (((this->columns) == (other->columns)) && ((this->rows) == (other->rows)))
    {
        int gap_ = std::max(this->gap, other->gap);
        
        matrix res = matrix(this->columns, this->rows, gap_);
#pragma omp parallel for num_threads(4)
        for (int i = 0; i < this->columns; i++)
        {
            for (int j = 0; j < this->rows; j++)
            {
                double t;
                t = this->get(i, j) + other->get(i, j);
                res.set(i, j, t);
            }
        }
        return res;
    }
    else
    {
        throw std::invalid_argument("Matrix dimensions do not match!");
    }
}
matrix matrix::substract(matrix *other)
{
    if (((this->columns) == (other->columns)) && ((this->rows) == (other->rows)))
    {
        int gap_ = std::max(this->gap, other->gap);
        matrix res = matrix(this->columns, this->rows, gap_);
#pragma omp parallel for num_threads(4)
        for (int i = 0; i < this->columns; i++)
        {
            for (int j = 0; j < this->rows; j++)
            {
                double t;
                t = this->get(i, j) - other->get(i, j);
                res.set(i, j, t);
            }
        }
        return res;
    }
    else
    {
        throw std::invalid_argument("Matrix dimensions do not match!");
    }
}

matrix matrix::transpose()
{
    matrix res = matrix(this->rows, this->columns, this->gap);
#pragma omp parallel for num_threads(4)
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            res.set(i,j, this->get(j, i));
        }
    }
    return res;
}

matrix matrix::scale(double by)
{
    matrix res = matrix(this->columns, this->rows, this->gap);
#pragma omp parallel for num_threads(4)
    for (int i = 0; i < this->columns; i++)
    {
        for (int j = 0; j < this->rows; j++)
        {
            res.set(i,j,this->get(i,j)*by);
        }
    }
    return res;
}
double matrix::GaussForward()
{
    int n = this->rows;
    int m = this->columns;
    double coef_ = 1;
    vector coefs=vector(n);
    for (int k = 0; k < n; k++) // k-номер строки
    {
        #pragma omp parallel for num_threads(4)
        for (int i=0;i<n;i++){
            coefs.set(i,1);
        }
    double temp;
    temp=this->get(k,k);
        if (temp==0) {
            for (int i=k++;i<n;i++){
                if (this->get(k,i)!=0){
                    temp=this->get(k,i);
                    this->swapRows(i,k);
                    coef_*=-1;
                    break;
                }}
                if (temp==0){
                    continue;
            }
        }                
        #pragma omp parallel for num_threads(4)          
        for (int i = 0; i < m; i++)  // i-номер столбца
        {
            this->set(i, k, this->get(i, k) / temp);//нормировка
            
        }   
        coef_=coef_*temp; 
         #pragma omp parallel for num_threads(4)
        for (int i = k + 1; i < n; i++)                         // i-номер следующей строки после k
        {
            double K = this->get(k, i) / this->get(k, k); // Коэффициент

            if (K!=0){coefs.set(i,1/K);}
            
            for (int j = 0; j < m; j++)                                 // j-номер столбца следующей строки после k
                this->set(j, i, this->get(j, i) - this->get(j, k) * K); // Зануление элементов матрицы ниже первого члена, преобразованного в единицу
        }
        for (int i=0;i<n;i++){
        coef_*=coefs.get(i);
    }
        
    }
    
    return coef_;
}
void matrix::GaussBackward()
{
    int n = this->rows;
    int m = this->columns;
    
#pragma omp parallel for num_threads(4)
    for (int k = n - 1; k > -1; k--) // k-номер строки
    {   double temp;
        temp=this->get(k, k);
        if (temp==0) {
            for (int i=k++;i<n;i++){
                if (this->get(k,i)!=0){
                    temp=this->get(k,i);
                    this->swapRows(i,k);
                    break;
                }
                if (temp==0){
                    continue;
                }
            }
        }           
        for (int i = m - 1; i > -1; i--) // i-номер столбца
            this->set(i, k, this->get(i, k) / temp);
        for (int i = k - 1; i > -1; i--) // i-номер следующей строки после k
        {
            double K = this->get(k, i) / this->get(k, k);
            for (int j = m - 1; j > -1; j--) // j-номер столбца следующей строки после k
                this->set(j, i, this->get(j, i) - this->get(j, k) * K);
        }
    }
}
matrix matrix::GaussJordan()
{
    int n = this->rows;
    matrix res = matrix(n, n, this->gap);
    matrix Matrix_Big = matrix(2 * n, n, this->gap);
    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            Matrix_Big.set(i, j, this->get(i, j));
            Matrix_Big.set(i + n, j, static_cast<int>(i==j));
        }

    double det=Matrix_Big.GaussForward();

    for (int i=0;i<n;i++){
        det*=Matrix_Big.get(i,i);
    }

if (det!=0){

    Matrix_Big.GaussBackward();} else {
         throw std::invalid_argument("determinant is zero!");
    }

#pragma omp parallel for num_threads(4)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res.set(j, i, Matrix_Big.get(j + n, i));

    return res;
}

matrix matrix::inverse()
{
    if (this->rows == this->columns)
    {
        return this->GaussJordan();
    }
    else
    {
        throw std::invalid_argument("Matrix is not square!");
    }
}

vector matrix::mul_by_vec_left(vector *other)
{
    int n = this->rows;
    int m = this->columns;
    if (m == other->getSize())
    {
        vector res = vector(n);
#pragma omp parallel for num_threads(4)
        for (int j = 0; j < n; j++)//строка
        {
            double temp;
            temp = 0;
            for (int i = 0; i < m; i++)//столбец
            {
                temp += this->get(i, j)*other->get(i);
            }
            res.set(j, temp);
        }
        return res;
    }
    else
    {
        throw std::invalid_argument("Sizes do not match!");
    }
} // todo
vector matrix::mul_by_vec_right(vector *other)
{
    int n = this->rows;
    int m = this->columns;
    if (n == other->getSize())
    {
        vector res = vector(n);
#pragma omp parallel for num_threads(4)
        for (int j = 0; j < m; j++)//столбец
        {
            double temp;
            temp = 0;
            for (int i = 0; i < n; i++)//строка
            {
                temp += this->get(j, i)*other->get(i);
            }
            res.set(j, temp);
        }
        return res;
    }
    else
    {
        throw std::invalid_argument("Sizes do not match!");
    }
}

double matrix::get_determinant()
{
    if (this->rows == this->columns)
    {matrix Clone=*this;
        double coefs = Clone.GaussForward();
        double res = 1;
        for (int i = 0; i < this->rows; i++)
        {
            res *= Clone.get(i, i);
        }
        res = res * coefs;
        return abs(res);
    }
    else
    {
        throw std::invalid_argument("Matrix is not square");
    }
}

matrix matrix::HouseholderMethod()
{
    matrix R = *this;
    int n = this->rows;
    matrix I = matrix(n, n);
    matrix H_ = matrix(n, n);
    double cond;
    double temp;
    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            I.set(i, j, static_cast<double>(i == j));
        }
    }
    matrix Q = I;
    for (int j = 0; j < n - 1; j++)
    {
        int m = n - j;
        matrix H=matrix (m,m);
        matrix Rj=matrix(m,m);
        #pragma omp parallel for num_threads(4)
        for (int i = 0; i < m; i++)
        {
            for (int k = 0; k < m; k++)
            {
                Rj.set(i, k, R.get(i+j,k+j));
            }
        }
        vector u = vector(m);
        cond = 0;
        for (int k = 1; k < m; k++)
        {
            temp = Rj.get(k,0);
            cond += temp * temp;
        }
        if (cond < 1e-15) {
            continue;
        }
        temp = Rj.get(0, 0);
        #pragma omp parallel for num_threads(4)
        for (int k = 0; k < m; k++)
        {u.set(k, Rj.get(k,0));}
        cond += temp * temp;
        cond=sqrt(cond);
        if (temp>=0)
        {
            cond*=-1.0;
        }
        u.set(0, u.get(0)+ cond);
        if (u.eucledianNorm()<1e-15)
        {
            continue;
        }
        u=u.scale(1.0/u.eucledianNorm());
        #pragma omp parallel for num_threads(4)
        for (int i = 0; i < m; i++)
        {
            for (int l = 0; l < m; l++)
            {
                H.set(i, l, (static_cast<double>(i == l) - 2 * u.get(i) * u.get(l)));
            }
        }
        Rj = Rj.multiply_right(&H);
        H_=I;
        #pragma omp parallel for num_threads(4)
        for (int i = 0; i < m; i++)
            {
            for (int l = 0; l < m; l++)
                {
                    
                    R.set(i+j, l+j, Rj.get(i,l));
                    H_.set(i+j, l+j, H.get(i,l));
                }}
                
        Q = Q.multiply_right(&H_);
    }
    Q = Q.transpose();
    R = R.multiply_left(&Q);
    return R;
}

matrix matrix::QRMethod()
{
    matrix res = *this;
    matrix prev = res;
    double cond;
    int n = res.rows;
    matrix I = matrix(n, n);
    double v = 0;
#pragma omp parallel for num_threads(4)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            I.set(i, j, 0);
        }
        I.set(i, i, 1);
    }
    for (int i=0;i<10000;i++)
    {
        res = res.HouseholderMethod();
        cond = res.substract(&prev).frob_norm();
        prev = res;
        if (cond <= 1e-15) {break;}
    } 
    return res;
}
vector matrix::eigenvalues()
{
    if (this->rows == this->columns)
    {
        matrix QRres = this->QRMethod();
        vector res = vector(QRres.rows);
#pragma omp parallel for num_threads(4)
        for (int i = 0; i < QRres.rows; i++)
        {
            res.set(i, QRres.get(i, i));
        }
        return res;
    }
    else
    {
        throw std::invalid_argument("Matrix is not square");
    }
} // todo

matrix matrix::readFromFile(std::ifstream& file){
    try{
    int rows_, cols;
    double temp;
    file >> rows_ >> cols;
    matrix res=matrix(cols,rows_);
    //std::cout<<cols<<" "<<rows_<<"\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (file >> temp) {
            std::cout<<temp;
            res.set(j,i,temp);}
        }
    }
    file.close();
    return res;}catch(const std::exception& e){
        std::cout<<"err_fileread"<<e.what();
        return matrix(0,0);
    }
}
matrix::matrix(std::ifstream& file){
    try{
    *this=readFromFile(file);}
    catch(const std::exception& e){
        std::cout<<"err_cons"<<e.what();
        *this=matrix(0,0);
    }
}