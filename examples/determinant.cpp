#include "..\headers\matrix.h"
#include <iostream>
int main()
{
    matrix example = matrix(3, 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            example.set(i, j, i + j + 1);
        }
    }
    std::cout << "A:\n";
    example.print();
    std::cout << "Det of A:" << example.get_determinant();

    return 0;
}