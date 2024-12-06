#ifndef INTARRAY_H
#define INTARRAY_H

#include<iostream>
#include<iomanip>
#include<thread>
#include<chrono>
#include<vector>
#include<future>
#include "RequestHandler.h"

#define PART_SIZE 150000 // threads partision size

class IntArray
{
private:
    int* arr;
    int arr_size;
    RequestHandler rh;

    void QsortNoThreads(int *array, long left, long right);
    void QsortThreads(int *array, long left, long right);
    void QsortThreadsPool(int *array, long left, long right);
    void time_spend(void (IntArray::*func)(int*, long, long), int*, long, long);
    void quicksort_part(int* array, long left, long right);//, std::shared_ptr<std::promise<void>> promise);

public:
    IntArray(const int &size);
    ~IntArray();
    void fillArray(int min = 0, int max = 1000);
    void printArray(int width = 16);
    void QsortThreads();
    void QsortNoThreads();
    void QsortThreadsPool();
};

#endif // QUICKSORT_H