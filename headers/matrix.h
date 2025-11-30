#include "vector.h"
#include <iostream>
#include <fstream>
#include <cstring>
#ifndef MATRIX_H // Include guard
#define MATRIX_H
class matrix
{
    double *self;
    int columns;
    int rows;
    int gap;
    int size;
    /// @brief умножение матриц
    /// @param left левый множитель
    /// @param right правый множитель
    /// @return произведение
    matrix multiply(matrix *left, matrix *right);
    /// @brief метод Гаусса-Жордана
    /// @return обратная матрица к данной
    matrix GaussJordan();
    /// @brief прямой ход метода Гаусса
    /// @param og изначальная матрица (отличается от this в методе Гаусса-Жордана)
    /// @return og после прямого хода
    double GaussForward(matrix *og);
    /// @brief обратный ход метода Гаусса
    /// @param og изначальная матрица (отличается от this в методе Гаусса-Жордана)
    void GaussBackward(matrix *og);
    /// @brief метод Хаусхолдера
    /// @param qr если true, возвращает следующую матрицу A(k)=R(k-1)Q(k-1) для QR-метода, иначе - полученную матрицу R (хессенбергову)
    /// @return если qr true, возвращает следующую матрицу A(k)=R(k-1)Q(k-1) для QR-метода, иначе - полученную матрицу R (хессенбергову)
    matrix HouseholderMethod(bool qr);
    matrix HouseholderMethod2();
    /// @brief сведение к блочно-диагональной матрице QR-методом (для поиска собственных значений)
    /// @return матрицу близкую к блочно-диагональной (с заданной постоянной точностью в 10^(-15))
    matrix QRMethod();
    /// @brief поменять местами строки (должно войти в метод Гаусса)
    /// @param row1 индекс строки 1
    /// @param row2 индекс строки 2
    void swapRows(int row1, int row2);
public:
    /// @brief получить элемент по индексам
    /// @param colId индекс столбца
    /// @param rowId индекс строки
    /// @return элемент
    double get(int colId, int rowId);
    /// @brief задать значение элемента
    /// @param colId индекс столбца
    /// @param rowId индекс строки
    /// @param value значение
    void set(int colId, int rowId, double value);  
    /// @brief умножить данную матрицу на other, где данная матрица - левый множитель
    /// @param other правый множитель
    /// @return произведение
    matrix multiply_left(matrix *other);
    /// @brief умножить данную матрицу на other, где данная матрица - правый множитель
    /// @param other левый множитель
    /// @return произведение
    matrix multiply_right(matrix *other);  
    /// @brief сложение матриц
    /// @param other второе слагаемое
    /// @return сумма
    matrix add(matrix *other);  
    /// @brief вычитание матриц
    /// @param other вычитаемое
    /// @return разность
    matrix substract(matrix *other);  
    /// @brief поиск обратной матрицы методом Гаусса-Жордана
    /// @return обратная матрица
    matrix inverse();
    /// @brief умножение матрицы на вектор, где матрица - левый множитель
    /// @param other вектор
    /// @return произведение
    vector mul_by_vec_left(vector *other);  
    /// @brief умножение матрицы на (транспонированный) вектор, где матрица - правый множитель
    /// @param other вектор
    /// @return произведение
    vector mul_by_vec_right(vector *other);  
    /// @brief поиск собственных значений матрицы QR-методом, где для поиска разложения используется метод Хаусхолдера (оно не работает и никто(я) не знает, почему)
    /// @return вектор собственных значений
    vector eigenvalues();
    /// @brief вычисление определителя через приведение к треугольному виду методом Гаусса
    /// @return определитель
    double get_determinant();  
    /// @brief транспонирование
    /// @return транспонированную матрицу
    matrix transpose(); 
    /// норма Фробениуса (в т.ч. для QR-метода) 
    double frob_norm();  
    /// @brief умножение на скаляр
    /// @param by скаляр
    /// @return произведение
    matrix scale(double by);  
    /// @brief вывод матрицы в консоль
    void print();  
    /// @brief вывод матрицы в файл
    /// @param of целевой файл
    void fprint(std::ofstream& of);
    matrix(int col, int rows_, int gap_ = 1);  
     matrix(const matrix &other);
    matrix &operator=(const matrix &other)
    {
        if (this != &other)
        {
            free(self); // Release old memory
            rows = other.rows;
            columns = other.columns;
            gap = other.gap;
            self = (double *)malloc((rows + gap) * columns * sizeof(double));
            std::memcpy(self, other.self, (rows + gap) * columns * sizeof(double));
        }
        return *this;
    };
    ~matrix();
};
#endif