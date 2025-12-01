#include "../headers/matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
int main()
{int n=5;
    std::string name="./results/mul_matrixes"+std::to_string(n)+".txt";
    std::ofstream outfile(name);
    matrix left = matrix(n, n);
    matrix right = matrix(n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            left.set(i, j, i*j+1);
            right.set(i, j, i + j);
        }
    }
    outfile<< "A:\n";
    left.fprint(outfile);
    outfile<< "B:\n";
    right.fprint(outfile);
    outfile<< "AB called by A:\n";
    auto start = std::chrono::high_resolution_clock::now();
    left.multiply_left(&right).fprint(outfile);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "MulM L: " << duration.count() << " ms" << std::endl;
    outfile<< "AB called by B:\n";
    start = std::chrono::high_resolution_clock::now();
    right.multiply_right(&left).fprint(outfile);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "MulM R: " << duration.count() << " ms" << std::endl;
    return 0;
}