#include "../headers/matrix.h"
#include <iostream>
#include <fstream>
#include <chrono>
int main()
{int n=5;
    std::string name="./results/eigenvalues"+std::to_string(n)+".txt";
    std::ofstream outfile(name);
    matrix example=matrix(n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            example.set(i, j, i + j + 1);
        }
    }
    outfile << "A:\n";
    example.fprint(outfile);
    outfile << "Eigenvalues of A:\n";
    auto start = std::chrono::high_resolution_clock::now();
    example.eigenvalues().fprint(outfile);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Eig: " << duration.count() << " ms" << std::endl;
    return 0;
}