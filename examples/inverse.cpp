#include "../headers/matrix.h"
#include <iostream>
#include <fstream> 
#include<cmath>
#include <chrono>
int main()
{int n=5;
    std::string name="./results/inverse"+std::to_string(n)+".txt";
    std::ofstream outfile(name);
    matrix example = matrix(n,n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            example.set(i, j, pow(i,j));
        }
    }
    outfile << "A:\n";
    example.fprint(outfile);
    outfile << "inverse of A:\n";
    auto start = std::chrono::high_resolution_clock::now();
    matrix res = example.inverse();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Inv: " << duration.count() << " ms" << std::endl;
    res.fprint(outfile);
    return 0;
}