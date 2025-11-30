#include "../headers/matrix.h"
#include <iostream>
#include <fstream>
int main()
{
    std::ofstream outfile("./results/mul_matrixes.txt");
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
    outfile<< "A:\n";
    left.fprint(outfile);
    outfile<< "B:\n";
    right.fprint(outfile);
    outfile<< "AB called by A:\n";
    left.multiply_left(&right).fprint(outfile);
    outfile<< "AB called by B:\n";
    right.multiply_right(&left).fprint(outfile);
    return 0;
}