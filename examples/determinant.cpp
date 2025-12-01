#include "../headers/matrix.h"
#include <iostream>
#include <fstream>
#include <chrono>
int main()
{int n=5;
    std::string name="./results/determinant"+std::to_string(n)+".txt";
    std::ofstream outfile(name);
    matrix example = matrix(n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            example.set(i, j, i + j + 1);
        }
    }
    outfile << "A:\n";
    example.fprint(outfile);
    auto start = std::chrono::high_resolution_clock::now();
    outfile << "Det of A=" << example.get_determinant();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Det: " << duration.count() << " ms" << std::endl;

    return 0;
}