// Header.h
#ifndef HEADER_H
#define HEADER_H

#include <vector>
using namespace std;

// �ƧǨ禡
void insertionSort(vector<int>& arr);
void quickSort(vector<int>& arr);
void mergeSort(vector<int>& arr);
void heapSort(vector<int>& arr);
void compositeSort(vector<int>& arr);

// �u��禡
vector<int> generateRandomData(int size);
void printData(const vector<int>& data);

// ���q�ɶ��ҪO
template<typename Func>
double timeSorting(Func sortFunc, vector<int> arr) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

#endif // HEADER_H
