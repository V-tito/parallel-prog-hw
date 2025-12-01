#include "../headers/matrix.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>
int main()
{std::string name="./results/output_all.txt";
    std::ofstream outfile(name);
    double AvE=0;
    double AvD=0;
    double AvI=0;
    double AvT=0;
    double AvMML=0;
    double AvMVL=0;
    double AvMMR=0;
    double AvMVR=0;
     std::srand(std::time({})); // use current time as seed for random generator
    for (int n=5;n<30;n+=5){
        outfile<<"n="<<n<<"\n";
    matrix example=matrix(n, n);
    int i=0;
    do
    {
       for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i>=j)
            example.set(i, j, std::rand()+1);
            else
            example.set(i, j, std::rand()%10-11);
        }
    }
    i++;
    outfile<<"gen attempt "<<i<<"\n";
    if (i>100) break;
    } while (example.get_determinant()==0);
    vector rightV = vector(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            rightV.set(i, i+j);
        }
    }
    matrix rightM = matrix(n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            rightM.set(i, j, i + j);
        }
    }
    for (int i=0;i<10;i++){
    auto start = std::chrono::high_resolution_clock::now();
    example.eigenvalues();
    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::nanoseconds>( end - start ).count();
    AvE+=duration;

    start = std::chrono::high_resolution_clock::now();
    example.get_determinant();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>( end - start ).count();
    AvD+=duration;

    start = std::chrono::high_resolution_clock::now();
    example.transpose();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>( end - start ).count();
    AvT+=duration;

    start = std::chrono::high_resolution_clock::now();
    example.inverse();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>( end - start ).count();
    AvI+=duration;

    start = std::chrono::high_resolution_clock::now();
    example.mul_by_vec_left(&rightV);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>( end - start ).count();
    AvMVL+=duration;

    start = std::chrono::high_resolution_clock::now();
    example.mul_by_vec_right(&rightV);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>( end - start ).count();
    AvMVR+=duration;

    start = std::chrono::high_resolution_clock::now();
    example.multiply_left(&rightM);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>( end - start ).count();
    AvMML+=duration;

    start = std::chrono::high_resolution_clock::now();
    rightM.multiply_right(&example);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>( end - start ).count();
    AvMMR+=duration;
    }
    outfile << "Eig: " << AvE/10.0 << " ns" << std::endl;
    outfile << "D: " << AvD/10.0 << " ns" << std::endl;
    outfile << "T: " << AvT/10.0 << " ns" << std::endl;
    outfile << "Inv: " << AvI/10.0 << " ns" << std::endl;
    outfile << "MML: " << AvMML/10.0 << " ns" << std::endl;
    outfile << "MMR: " << AvMMR/10.0 << " ns" << std::endl;
    outfile << "MVL: " << AvMVL/10.0 << " ns" << std::endl;
    outfile << "MVR: " << AvMVR/10.0 << " ns" << std::endl;
}
    return 0;
}