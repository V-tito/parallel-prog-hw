#include "../headers/matrix.h"
#include <iostream>
#include <fstream> 
int main()
{
    std::ofstream outfile("./results/transpose.txt");
    matrix example = matrix(3, 3,1);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            example.set(i, j, i+1);
        }
    }
    outfile << "A:\n";
    example.fprint(outfile);
    outfile << "A transposed:\n";
    matrix res = example.transpose();
    res.fprint(outfile);
    return 0;
}