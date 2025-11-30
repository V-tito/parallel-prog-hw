#include "../headers/matrix.h"
#include <iostream>
#include <fstream>
int main()
{
    std::ofstream outfile("./results/determinant.txt");
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
    outfile << "Det of A=" << example.get_determinant();

    return 0;
}