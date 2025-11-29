#include "..\headers\matrix.h"
#include <iostream>
int main()
{
    matrix left = matrix(3, 3);
    matrix right = matrix(3, 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            left.set(i, j, static_cast<double>(i == j));
            right.set(i, j, i + j);
        }
    }
    std::cout << "A:\n";
    left.print();
    std::cout << "B:\n";
    right.print();
    std::cout << "AB called by A:\n";
    left.multiply_left(&right).print();
    std::cout << "AB called by B:\n";
    right.multiply_right(&left).print();
    return 0;
}