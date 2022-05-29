#include "CVector.h"
#include "CVector0.h"

#include <chrono>
#include <omp.h>
#include <cstdlib>

void parallel(int arr_size, size_t nn)
{
    vector<CVector0> vec1;
    vector<CVector0> vec2;
    vector<CVector0> vec_rez;

    double* arr = (double*)malloc(sizeof(double) * nn);
    for (int i = 0; i < arr_size; i++)
    {

        for (int j = 0; j < nn; j++)
        {
            arr[j] = i + (double)rand()/((double)rand()-10);

        }

        vec1.push_back(CVector0( arr_size, "data1"));
        vec2.push_back(CVector0( arr_size , "data2"));
    }


    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < arr_size; i++)
    {
        vec_rez.push_back(vec1[i] + vec2[i]);
    }
    auto end = std::chrono::system_clock::now();
    int elapsed_ms = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    std::cout << "Make add operator without parallelization: " << elapsed_ms << " ms" << endl;


    auto start1 = std::chrono::system_clock::now();

    int d = 0;
#pragma omp parallel for shared(vec1, vec2, vec_rez) private(d)
    for (d = 0; d < arr_size; d++)
    {
        vec_rez[d] = vec1[d] + vec2[d];
    }
    auto end1 = std::chrono::system_clock::now();
    int elapsed_marr_size = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count());
    std::cout << "Make add operator with parallelization: " << elapsed_marr_size << "ms" << endl;

    //
    vec1.clear();
    vec2.clear();
    vec_rez.clear();
}