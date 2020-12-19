#include <fstream>
#include <bits/stdc++.h>
#include "Sorting.h"
#include "GenerateFile.h"

Sorting::Sorting(){

}

Sorting::~Sorting(){
  delete[] quickArr;
  delete[] mergeArr;
  delete[] selectionArr;
  delete[] insertionArr;
  delete[] bubbleArr;
}

void Sorting::readFile(string filename){
  //nt totalElements = 0;
  ifstream readfile;
  bool running = true;
  readfile.open(filename);
  if(readfile.fail()){
    //file could not be opened
    cout << "Failed to open file. " << endl;
    while(running){
      cout << "Do you want to randomly generate numbers in a file? (y/n) " << endl;
      char input;
      cin >> input;
      if(input == 'y'){
        GenerateFile gf;
        gf.toFile();
        //FIXME!!!!
        readfile.open("randomNums.txt");
        readfile >> totalElements;
        quickArr = new double[totalElements];
        mergeArr = new double[totalElements];
        selectionArr = new double[totalElements];
        insertionArr = new double[totalElements];
        bubbleArr = new double[totalElements];

        for(int i = 0; i < totalElements; ++i){
          double ele = 0;
          readfile >> ele;
          //cout << ele << endl;
          quickArr[i] = ele;
          mergeArr[i] = ele;
          selectionArr[i] = ele;
          insertionArr[i] = ele;
          bubbleArr[i] = ele;
        }
        sortAll();
        running = false;
      }else if(input == 'n'){
        cout << "Breaking out of program...Try entering a correct file next time!" << endl;
        //readfile.close();
        //reak;
        running = false;
      }else{
        cout << "try entering y/n" << endl;
      }
    }
  }else{
    //file was successfully opened
    readfile >> totalElements;
    quickArr = new double[totalElements];
    mergeArr = new double[totalElements];
    selectionArr = new double[totalElements];
    insertionArr = new double[totalElements];
    bubbleArr = new double[totalElements];

    for(int i = 0; i < totalElements; ++i){
      double ele = 0;
      readfile >> ele;
      //cout << ele << endl;
      quickArr[i] = ele;
      mergeArr[i] = ele;
      selectionArr[i] = ele;
      insertionArr[i] = ele;
      bubbleArr[i] = ele;
    }
    //printArr(quickArr, totalElements);
    sortAll();
  }
}

void Sorting::printArr(double arr[], int n){
  cout << "Printing Array: ";
  for (int i=0; i < n; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

void Sorting::swap(double arr[], int a, int b){
  //cout << "in swapp" << endl;
  double temp = arr[a];
  arr[a] = arr[b];
  arr[b] = temp;
}

int Sorting::partition(double arr[], int left, int right){
  //cout << "in partition " <<endl;

  int pivot = arr[(left + right) / 2];
    while (left <= right)
    {
      //Objects to Left of Pivot in Array
      while (arr[left] < pivot) {
        left++;
      }
      //Objects to Right of Pivot in Array
      while (arr[right] > pivot) {
        right--;
      }
      //Swap Left and Right Objects
      if (left <= right) {
        swap(arr, left, right);
        left++;
        right--;
      }
    }
    return left;
}

void Sorting::quickSort(double arr[], int left, int right){
  //cout << "in quick" << endl;
 int idx = partition(arr, left, right);
  if(left < idx - 1) {
    quickSort(arr, left, idx - 1);
  }
  if(right > idx) {
    quickSort(arr, idx, right);
  }
}

void Sorting::mergeSort(double myArray[], int s, int e){
  if(s < e){

    //splits the array into two arrays
    int mid = ((s + e) / 2);

    //recursively sorting
    mergeSort(myArray, s, mid);
    mergeSort(myArray, mid + 1, e);

    //sorts the newly split arrays
    merge(myArray, s, mid, e);
  }
}

void Sorting::merge(double myArray[], int s, int m, int e){
  //keeping track of the variables
int start = s;
int end = m + 1;

//new array and position
double Arr[(e - s) + 1];
int x = 0;

//for loop sorting elements in the new array
for(int i = s; i <= e; i++){

  if(start > m){
    //checks if first sort of the array is over
    myArray[x++] = myArray[end++];
  }

  //checks if second sort is over
   else if(end > e){
     myArray[x++] = myArray[start++];
   }

   //which element is smaller
   else if(myArray[start] < myArray[end]){
     myArray[x++] = myArray[start++];
   }
   else{
     myArray[x++] = myArray[end++];
   }
 }

 //array now sorted
  for(int j = 0; j < x; j++) {
     myArray[s++] = myArray[j] ;
  }
}

void Sorting::selectionSort(double arr[], int n){
  int i, j, minIndex, tmp;
  //minIndex is compared with all other elements of the array
  //switches it with the lowest element in the array
  for(i = 0; i < n-1; i++){
    minIndex = i;

    for(j = i+1; j < n; j++){
      if(arr[j] < arr[minIndex]){
        minIndex = j;
      }

      if(minIndex != i){
        tmp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = tmp;
      }
    }
  }
}

// void Sorting::selectionSwap(double *xp, double *yp){
//   double temp = *xp;
//   *xp = *yp;
//   *yp = temp;
// }

void Sorting::insertionSort(double arr[], int n){
  for(int j = 1; j < n; ++j){ //marker
    double temp  = arr[j]; //store marker item
    int k = j;
    while(k > 0 && arr[k-1] >= temp){ //while the thing to the left is larger, shift
      arr[k] = arr[k-1];
      --k;
    }
    arr[k] = temp; //put marked item in right spot
  }
}

void Sorting::bubbleSort(double arr[]){
  //compares each index with its next element
  for(int i = 0; i < totalElements; ++i){
    double temp = 0;
    for(int j = i; j < totalElements-1; ++j){
      if(arr[j] > arr[j+1]){
        temp = arr[j+1];
        arr[j+1] = arr[j];
        arr[j] = temp;
      }
    }
  }
}

void Sorting::sortAll(){
  int n = sizeof(quickArr)/sizeof(quickArr[0]);
  clock_t quickStartTime = clock();
  quickSort(quickArr, 0, n - 1);
  clock_t quickEndTime = clock();

  double duration = ((quickEndTime - quickStartTime)/(double)(CLOCKS_PER_SEC));//(double)(quickEndTime - quickStartTime);
  cout << "Sorting Algorithm: Quick Sort" << endl;
  //cout << "Sorted Array: ";
  //printArr(quickArr, totalElements);
  cout << "Time Sort Started: " << quickStartTime << endl;
  cout << "Time Sort Ended: " << quickEndTime << endl;
  cout << "Duration of Sorting: " << duration << endl << endl;


  //--------MERGE SORT----------
  int m = sizeof(mergeArr)/sizeof(mergeArr[0]);
  clock_t mergeStartTime = clock();
  mergeSort(mergeArr, 0, totalElements - 1);
  clock_t mergeEndTime = clock();

  double durationmerge = ((mergeEndTime - mergeStartTime)/(double)(CLOCKS_PER_SEC));//(double)(quickEndTime - quickStartTime);
  cout << "Sorting Algorithm: Merge Sort" << endl;
  //cout << "Sorted Array: ";
  //printArr(mergeArr, totalElements);
  cout << "Time Sort Started: " << mergeStartTime << endl;
  cout << "Time Sort Ended: " << mergeEndTime << endl;
  cout << "Time It Took For Sorting: " << durationmerge << endl << endl;
  //
  //--------selction SORT----------
  int k = sizeof(selectionArr)/sizeof(selectionArr[0]);
  clock_t selectionStartTime = clock();
  selectionSort(selectionArr, totalElements);
  clock_t selectionEndTime = clock();

  double durationselection = ((selectionEndTime - selectionStartTime)/(double)(CLOCKS_PER_SEC));//(double)(quickEndTime - quickStartTime);
  cout << "Sorting Algorithm: Selection Sort" << endl;
  //cout << "Sorted Array: ";
  //printArr(selectionArr, totalElements);
  cout << "Time Sort Started: " << selectionStartTime << endl;
  cout << "Time Sort Ended: " << selectionEndTime << endl;
  cout << "Time It Took For Sorting: " << durationselection << endl << endl;

  //--------insertion SORT----------
  int z = sizeof(insertionArr)/sizeof(insertionArr[0]);
  clock_t insertionStartTime = clock();
  insertionSort(insertionArr, totalElements);
  clock_t insertionEndTime = clock();

  double durationinsertion = ((insertionEndTime - insertionStartTime)/(double)(CLOCKS_PER_SEC));//(double)(quickEndTime - quickStartTime);
  cout << "Sorting Algorithm: Insertion Sort" << endl;
  //cout << "Sorted Array: ";
  //printArr(insertionArr,totalElements);
  cout << "Time Sort Started: " << insertionStartTime << endl;
  cout << "Time Sort Ended: " << insertionEndTime << endl;
  cout << "Time It Took For Sorting: " << durationinsertion << endl << endl;

  //--------BUBBLE SORT----------
  int y = sizeof(bubbleArr)/sizeof(bubbleArr[0]);
  clock_t bubbleStartTime = clock();
  bubbleSort(bubbleArr);
  clock_t bubbleEndTime = clock();

  double durationbubble = ((bubbleEndTime - bubbleStartTime)/(double)(CLOCKS_PER_SEC));//(double)(quickEndTime - quickStartTime);
  cout << "Sorting Algorithm: Bubble Sort" << endl;
  //cout << "Sorted Array: ";
  //printArr(bubbleArr, totalElements);
  cout << "Time Sort Started: " << bubbleStartTime << endl;
  cout << "Time Sort Ended: " << bubbleEndTime << endl;
  cout << "Time It Took For Sorting: " << durationbubble << endl << endl;
}
