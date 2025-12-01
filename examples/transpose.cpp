#include "../headers/matrix.h"
#include <iostream>
#include <fstream> 
#include <chrono>
int main()
{int n=5;
    std::string name="./results/transpose"+std::to_string(n)+".txt";
    std::ofstream outfile(name);
    matrix example = matrix(n, n,1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            example.set(i, j, i+1);
        }
    }
    outfile << "A:\n";
    example.fprint(outfile);
    outfile << "A transposed:\n";
    auto start = std::chrono::high_resolution_clock::now();
    matrix res = example.transpose();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "T: " << duration.count() << " ms" << std::endl;
    res.fprint(outfile);
    return 0;
}