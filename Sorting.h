#include <iostream>
using namespace std;

class Sorting{
public:
  Sorting();
  ~Sorting();

  void readFile(string file);

  void quickSort(double arr[], int low, int high);
  int partition(double arr[], int leftmostIndex, int rightmostIndex);
  void swap(double arr[], int a, int b);

  void mergeSort(double arr[],int l,int r);
  void merge(double myArray[], int s, int m, int e);

  void selectionSort(double a[], int n);
  //void selectionSwap(double *xp, double *yp);
  void insertionSort(double arr[], int length);
  void bubbleSort(double arr[]);
  void sortAll();
  void printArr(double arr[], int n);

  double *quickArr;
  double *mergeArr;
  double *selectionArr;
  double *insertionArr;
  double* bubbleArr;
  int totalElements = 0;
};
