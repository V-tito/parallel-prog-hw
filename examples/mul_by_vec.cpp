#include "../headers/matrix.h"
#include <iostream>
#include <fstream>
#include <chrono>
int main()
{int n=5;
    std::string name="./results/mul_by_vec"+std::to_string(n)+".txt";
    std::ofstream outfile(name);
    matrix left = matrix(n, n);
    vector right = vector(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            left.set(i, j, i+j+1);
            right.set(i, i+j);
        }
    }
    outfile << "A:\n";
    left.fprint(outfile);
    outfile << "B:\n";
    right.fprint(outfile);
    outfile << "AB called by A:\n";
    auto start = std::chrono::high_resolution_clock::now();
    left.mul_by_vec_left(&right).fprint(outfile);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "MulV L: " << duration.count() << " ms" << std::endl;
    outfile << "BA called by A:\n";
    start = std::chrono::high_resolution_clock::now();
    left.mul_by_vec_right(&right).fprint(outfile);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "MulV R: " << duration.count() << " ms" << std::endl;
    return 0;
}