#include "../headers/matrix.h"
#include <iostream>
#include <fstream> 
int main()
{
    std::ofstream outfile("./results/inverse.txt");
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
    outfile << "inverse of A:\n";
    matrix res = example.inverse();
    res.fprint(outfile);
    return 0;
}