// Header.h
#ifndef HEADER_H
#define HEADER_H

#include <vector>
using namespace std;

// 排序函式
void insertionSort(vector<int>& arr);
void quickSort(vector<int>& arr);
void mergeSort(vector<int>& arr);
void heapSort(vector<int>& arr);
void compositeSort(vector<int>& arr);

// 工具函式
vector<int> generateRandomData(int size);
void printData(const vector<int>& data);

// 測量時間模板
template<typename Func>
double timeSorting(Func sortFunc, vector<int> arr) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

#endif // HEADER_H
