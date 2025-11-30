#include "../headers/matrix.h"
#include <iostream>
#include <fstream>
int main()
{
    std::ofstream outfile("./results/eigenvalues.txt");
    matrix example = matrix(3, 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            example.set(i, j, i + j + 1);
        }
    }
    outfile << "A:\n";
    example.fprint(outfile);
    outfile << "Eigenvalues of A:\n";
    example.eigenvalues().fprint(outfile);
    return 0;
}