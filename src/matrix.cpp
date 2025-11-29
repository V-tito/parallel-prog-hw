#include <omp.h>
#include <stdlib.h>
#include <algorithm>
#include <stdexcept>
#include "..\headers\matrix.h"
#include <iostream>
class matrix
{
private:
    double *self;
    int columns;
    int rows;
    int gap;
    int size;
    matrix multiply(matrix *left, matrix *right) {}
    matrix GaussJordan() {}
    double GaussForward(matrix *og) {}
    void GaussBackward(matrix *og) {}
    matrix HouseholderMethod(bool qr) {}
    matrix QRMethod() {}
    void swapRows(int row1, int row2) {}

public:
    double get(int colId, int rowId)
    {
    }
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
void matrix::swapRows(int row1, int row2)
{
    double temp;
    for (int i = 0; i < this->columns; i++)
    {
        temp = this->get(i, row1);
        this->set(i, row1, this->get(i, row2));
        this->set(i, row2, temp);
    }
}
void matrix::print()
{
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            std::cout << this->get(j, i);
        }
        std::cout << "\n";
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

matrix::matrix(int col, int rows_, int gap_ = 1)
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
    res = sqrt(res);
    return res;
}
matrix matrix::multiply(matrix *left, matrix *right)
{
    int gap_ = std::max(left->gap, right->gap);
    double t;
    matrix res = matrix(right->columns, left->rows, gap_);
#pragma omp parallel for
    for (int i = 0; i < right->columns; i++)
    {
        for (int j = 0; j < left->rows; j++)
        {
            res.set(i, j, 0);
        }
    }
#pragma omp parallel for
    for (int j = 0; j < right->columns; j++)
    {
        for (int i = 0; i < left->rows; i++)
        {

            t = 0;
            for (int k = 0; k < left->columns; k++)
            {
                for (int m = 0; m < right->rows; m++)
                {
                    t += left->get(k, i) * right->get(j, m);
                }
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
        double t;
        matrix res = matrix(this->columns, this->rows, gap_);
#pragma omp parallel for
        for (int i = 0; i < this->columns; i++)
        {
            for (int j = 0; j < this->rows; j++)
            {
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
        double t;
        matrix res = matrix(this->columns, this->rows, gap_);
#pragma omp parallel for
        for (int i = 0; i < this->columns; i++)
        {
            for (int j = 0; j < this->rows; j++)
            {
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
    double *ptr = res.self;
#pragma omp parallel for
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            *ptr = this->get(j, i);
            ptr++;
        }
        ptr += res.gap;
    }
    return res;
}

matrix matrix::scale(double by)
{
    matrix res = matrix(this->columns, this->rows, this->gap);
    double *ptr = res.self;
#pragma omp parallel for
    for (int i = 0; i < this->columns; i++)
    {
        for (int j = 0; j < this->rows; j++)
        {
            *ptr *= by;
            ptr++;
        }
        ptr += this->gap;
    }
    return res;
}
double matrix::GaussForward(matrix *og)
{
    matrix Clone = *og;
    int n = this->rows;
    int m = this->columns;
    double coef = 1;
#pragma omp parallel for
    for (int k = 0; k < n; k++) // k-номер строки
    {
        for (int i = 0; i < m; i++)                             // i-номер столбца
            this->set(i, k, this->get(i, k) / Clone.get(k, k)); // Деление k-строки на первый член !=0 для преобразования его в единицу
        for (int i = k + 1; i < n; i++)                         // i-номер следующей строки после k
        {
            double K = this->get(k, i) / this->get(k, k); // Коэффициент
            coef *= K;
            for (int j = 0; j < m; j++)                                 // j-номер столбца следующей строки после k
                this->set(j, i, this->get(j, i) - this->get(j, k) * K); // Зануление элементов матрицы ниже первого члена, преобразованного в единицу
        }
        for (int i = 0; i < n; i++) // Обновление, внесение изменений в начальную матрицу
            for (int j = 0; j < n; j++)
                Clone.set(j, i, this->get(j, i));
    }
    return coef;
}
void matrix::GaussBackward(matrix *og)
{
    int n = this->rows;
    int m = this->columns;
#pragma omp parallel for
    for (int k = n - 1; k > -1; k--) // k-номер строки
    {
        for (int i = m - 1; i > -1; i--) // i-номер столбца
            this->set(i, k, this->get(i, k) / og->get(k, k));
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
    matrix xirtaM = matrix(n, n, this->gap);
#pragma omp parallel for
    for (int i = 0; i < n; i++)
        xirtaM.set(i, i, 1);
#pragma omp parallel for
    matrix Matrix_Big = matrix(2 * n, n, this->gap);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            Matrix_Big.set(i, j, this->get(i, j));
            Matrix_Big.set(i + n, j, xirtaM.get(i, j));
        }

    // Прямой ход (Зануление нижнего левого угла)
    Matrix_Big.GaussForward(this);

    // Обратный ход (Зануление верхнего правого угла)
    Matrix_Big.GaussBackward(this);

// Отделяем от общей матрицы
#pragma omp parallel for
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            xirtaM.set(j, i, Matrix_Big.get(j + n, i));

    return xirtaM;
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
        double temp;
#pragma omp parallel for
        for (int j = 0; j < n; j++)
        {
            temp = 0;
            for (int i = 0; i < m; i++)
            {
                temp += this->get(j, i);
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
        double temp;
#pragma omp parallel for
        for (int j = 0; j < m; j++)
        {
            temp = 0;
            for (int i = 0; i < n; i++)
            {
                temp += this->get(j, i);
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
    {
        double coefs = this->GaussForward(this);
        double res = 0;
#pragma omp parallel for
        for (int i = 0; i < this->rows; i++)
        {
            res += this->get(i, i);
        }
        res = res / coefs;
        return res;
    }
    else
    {
        throw std::invalid_argument("Matrix is not square");
    }
}

matrix matrix::HouseholderMethod(bool qr)
{
    matrix R = *this;
    int n = this->rows;
    double temp;
    double cond;
    matrix I = matrix(n, n);
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            I.set(i, j, 0);
        }
        I.set(i, i, 1);
    }
    matrix Q = I;
#pragma omp parallel for
    for (int j = 0; j < n - 1; j++)
    {
        int m = n - j;
        matrix H = I;
        vector u = vector(m);
        cond = 0;
        for (int k = 1; k < m; k++)
        {
            temp = this->get(j + k, j);
            cond += temp * temp;
            u.set(k, temp);
        }
        if (cond > 0)
        {
            temp = this->get(j, j);
            u.set(0, temp);
            cond += temp * temp;
            for (int k = 0; k < m; k++)
            {
                u.set(k, u.get(k) + cond);
            }
            for (int i = 0; i < m; i++)
            {
                for (int l = 0; l < m; l++)
                {
                    H.set(j + i, j + l, (static_cast<int>(i == l) - 2 * u.get(i) * u.get(l)));
                }
            }
        }
        else
        {
            for (int i = 0; i < m; i++)
            {
                for (int l = 0; l < m; l++)
                {
                    H.set(j + i, j + l, (static_cast<int>(i == l)));
                }
            }
        }
        for (int k = j; k < n; k++)
        {
            for (int l = j; l < n; l++)
            {
                R.set(k, l, R.get(k, l));
            }
        }
        Q = Q.multiply_right(&H);
        R = R.multiply_right(&H);
    }
    Q = Q.transpose();
    if (qr)
    {
        R = R.multiply_left(&Q);
    }
    return R;
}

matrix matrix::QRMethod()
{
    matrix res = this->HouseholderMethod(false);
    matrix prev = res;
    double cond;
    int n = res.rows;
    matrix I = matrix(n, n);
    double v = 0;
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            I.set(i, j, 0);
        }
        I.set(i, i, 1);
    }
    do
    {
        res = res.HouseholderMethod(true);
        cond = res.substract(&prev).frob_norm();
        prev = res;
    } while (cond > 0.000000000000001);
    return res;
}
vector matrix::eigenvalues()
{
    if (this->rows == this->columns)
    {
        matrix QRres = this->QRMethod();
        vector res = vector(QRres.rows);
#pragma omp parallel for
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