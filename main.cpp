//
//  main.cpp
//
// Final Project
// Project 5 - Sorting Algorithms
// CS 20A - Data Structures C++
// Professor Serghei Mangul
//
//  Created by Nathalie Madrigal on 11/25/18.
//  Copyright © 2018 SMCC Software. All rights reserved.

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <chrono>

using namespace std;

//class to get time calculation functions
class Timer {
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    double elapsed() const {
        return std::chrono::duration_cast<second_>
        (clock_::now() - beg_).count(); }
    
private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};

//Class containing sorting algorithms functions;
class sortingAlgorithms {
public:
    void mergeSort(int *arr, int l, int r);
    void bubbleSort(int *arr, int len);
    void insertionSort(int *arr, int len);
    void selectionSort(int *arr, int len);
    void sortedMerge(int *arr, int l, int m, int r);
};

//Bubble sort function definition
void sortingAlgorithms::bubbleSort(int *arr, int len) {
    int temp;
    for(int i = 0; i < len; i++){
        for(int j = len - 1; j > i; j--) {
            if(arr[j] < arr[j-1]) {
                temp = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

//Insertion sort function definition
void sortingAlgorithms::insertionSort(int *arr, int len) {
    for(int j = 1; j < len; j++) {
        int key = arr[j];
        int i = j - 1;
        while(i > -1 && arr[i] > key) {
            arr[i+1] = arr[i];
            i--;
        }
        arr[i+1] = key;
    }
}

//Selection sort function definition
void sortingAlgorithms::selectionSort(int *arr, int len) {
    int i, j, k;
    for (i = 0; i < len - 1; i++) {
        k = i;
        for (j = i+1; j < len; j++) {
            if (arr[j] < arr[k]) {
                k = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[k];
        arr[k] = temp;
    }
}

//Merge sort helper function - To merge two sorted arrays
void sortingAlgorithms::sortedMerge(int *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];
    
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1+ j];
    }
    
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

//Merge sort function definition
void sortingAlgorithms::mergeSort(int *arr, int l, int r) {
    if (l < r) {
        int m = l + ((r - l) / 2);
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        sortedMerge(arr, l, m, r);
    }
}

//Given an array and its size this function analyzes them
void analyzer(int *arr,int n)
{
    //Object to keep time
    Timer timer;
    //Object to get access to sorting algorithms
    sortingAlgorithms sorts;
    
    int arrays[100][n];
    
    double bubbleSortTime;
    //Creating 100 copies of array for bubble sort
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < n; j++) {
            arrays[i][j] = arr[j];
        }
    }
    //Bubble sort execution
    timer.reset();
    for(int i = 0; i < 100; i++) {
        sorts.bubbleSort(arrays[i], n);
    }
    bubbleSortTime = timer.elapsed();
    cout << "Bubble sort: " << bubbleSortTime << " seconds" << endl;
    
    double insertionSortTime;
    //Creating 100 copies of array for insertion sort
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < n; j++) {
            arrays[i][j] = arr[j];
        }
    }
    //Insertion sort execution
    timer.reset();
    for(int i = 0; i < 100; i++) {
        sorts.insertionSort(arrays[i], n);
    }
    insertionSortTime = timer.elapsed();
    cout << "Insertion sort: " << insertionSortTime << " seconds" << endl;
    
    double selectionSortTime;
    //Creating 100 copies of array for selection sort
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < n; j++) {
            arrays[i][j] = arr[j];
        }
    }
    //Selection sort execution
    timer.reset();
    for(int i = 0; i < 100; i++) {
        sorts.selectionSort(arrays[i], n);
    }
    selectionSortTime = timer.elapsed();
    cout << "Selection sort: " << selectionSortTime << " seconds" << endl;
    
    
    double mergeSortTime;
    //Creating 100 copies of array for merge sort
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < n; j++) {
            arrays[i][j] = arr[j];
        }
    }
    //Merge sort execution
    timer.reset();
    for(int i = 0; i < 100; i++) {
        sorts.mergeSort(arrays[i], 0, n - 1);
    }
    mergeSortTime = timer.elapsed();
    cout << "Merge sort: " << mergeSortTime << " seconds" << endl;
    cout << endl << "------------------------------------"<< endl;
}

int main() {
    
    int n = 10000;
    int arr[n];
    
    cout<<endl<<"(Random Array) \n"<<endl;
    for(int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
    analyzer(arr,n);
    
    cout<<endl<<"(Almost sorted Arrays) \n"<<endl;
    int marr[3] = {2,5,10};
    for(int mi=0;mi<3;mi++)
    {
        int m = marr[mi];
        for(int i = 0; i < n; i++) {
            arr[i] = i;
        }
        for(int i = 0; i < m; i++) {
            int indx = rand() % n;
            arr[indx] = (i+1)*n+rand()%n;
        }
        cout<<"mutations (m) = "<<m<<endl;
        analyzer(arr,n);
    }
    
    cout<<endl<<"(Fully unsorted Array/sorted wrong order) \n"<<endl;
    for(int i = 0; i < n; i++) {
        arr[i] = n-i;
    }
    analyzer(arr,n);
    
    
    return 0;
    //bubbleSort(arr1, n);
}
