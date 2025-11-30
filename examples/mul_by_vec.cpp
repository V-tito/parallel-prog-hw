#include "../headers/matrix.h"
#include <iostream>
#include <fstream>
int main()
{
    std::ofstream outfile("./results/mul_by_vec.txt");
    matrix left = matrix(3, 3);
    vector right = vector(3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            left.set(i, j, static_cast<double>(i == j));
            right.set(i, i);
        }
    }
    outfile << "A:\n";
    left.fprint(outfile);
    outfile << "B:\n";
    right.fprint(outfile);
    outfile << "AB called by A:\n";
    left.mul_by_vec_left(&right).fprint(outfile);
    outfile << "BA called by A:\n";
    left.mul_by_vec_right(&right).fprint(outfile);
    return 0;
}