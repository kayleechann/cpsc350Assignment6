#include <fstream>
#include <bits/stdc++.h>
#include "Sorting.h"
#include "GenerateFile.h"

Sorting::Sorting(){
  //constructor
}

//destructor
Sorting::~Sorting(){
  delete[] quickArr;
  delete[] mergeArr;
  delete[] selectionArr;
  delete[] insertionArr;
  delete[] bubbleArr;
}

//read in data from file to dynamically allocate arrays
void Sorting::readFile(string filename){
  ifstream readfile;
  bool running = true;
  readfile.open(filename);
  if(readfile.fail()){
    // if file could not be opened
    cout << "Failed to open file. " << endl;
    //ask user if they would like a file to be generated for them with random numbers
    while(running){
      cout << "Do you want to randomly generate numbers in a file? (y/n) " << endl;
      char input;
      cin >> input;
      if(input == 'y'){
        GenerateFile gf;
        gf.toFile();
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
          quickArr[i] = ele;
          mergeArr[i] = ele;
          selectionArr[i] = ele;
          insertionArr[i] = ele;
          bubbleArr[i] = ele;
        }
        sortAll();
        readfile.close();
        running = false;
      }else if(input == 'n'){
        //exit program is user says no
        cout << "Breaking out of program...Try entering a correct file next time!" << endl;
        running = false;
      }else{
        //asks users for valid input in order to continue
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
      quickArr[i] = ele;
      mergeArr[i] = ele;
      selectionArr[i] = ele;
      insertionArr[i] = ele;
      bubbleArr[i] = ele;
    }
    readfile.close();
    sortAll();
  }
}

//swap() is used in quick sort to swap numbers to the correct place fter partitioning the array
void Sorting::swap(double arr[], int a, int b){
  double temp = arr[a];
  arr[a] = arr[b];
  arr[b] = temp;
}

/* Takes last element of pivot and places in in correc orde
  Also continually checks pivot element in sorted array*/
int Sorting::partition(double arr[], int left, int right){
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
 int idx = partition(arr, left, right);
  if(left < idx - 1) {
    quickSort(arr, left, idx - 1);
  }
  if(right > idx) {
    quickSort(arr, idx, right);
  }
}

void Sorting::mergeSort(double arr[], int s, int e){
  if(s < e){
    //splits the array into two arrays
    int mid = ((s + e) / 2);
    //sorts recursively
    mergeSort(arr, s, mid);
    mergeSort(arr, mid + 1, e);
    //sort the newly sorted arrays and merges them
    merge(arr, s, mid, e);
  }
}

void Sorting::merge(double myArray[], int s, int m, int e){
  int start = s;
  int end = m + 1;
  double Arr[(e - s) + 1];
  int x = 0;
  //sort elements in new array
  for(int i = s; i <= e; i++){
    if(start > m){ //checks if first sort of the array is over
      myArray[x++] = myArray[end++];
    } else if(end > e){ //checks if second sort is over
     myArray[x++] = myArray[start++];
   }else if(myArray[start] < myArray[end]){ //getting the smaller element
     myArray[x++] = myArray[start++];
   }else{
     myArray[x++] = myArray[end++];
   }
 }

  for(int j = 0; j < x; j++){ //array is now sorted
     myArray[s++] = myArray[j] ;
  }
}

void Sorting::selectionSort(double arr[], int n){
  int i, j, min, tmp;
  //min is smallest and used to compare every element with it; it switches it with the lowest element in the array
  for(i = 0; i < n-1; i++){
    min = i;

    for(j = i+1; j < n; j++){
      if(arr[j] < arr[min]){
        min = j;
      }

      if(min != i){
        tmp = arr[i];
        arr[i] = arr[min];
        arr[min] = tmp;
      }
    }
  }
}

void Sorting::insertionSort(double arr[], int n){
  for(int j = 1; j < n; ++j){
    double temp  = arr[j]; //store marker item
    int k = j;
    while(k > 0 && arr[k-1] >= temp){ //if left item is larger, switch elements
      arr[k] = arr[k-1];
      --k;
    }
    arr[k] = temp; //put marked item in right spot
  }
}

// Bubble Sort compares each index with its next element
void Sorting::bubbleSort(double arr[]){
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
  cout << "Time Sort Started: " << quickStartTime << endl;
  cout << "Time Sort Ended: " << quickEndTime << endl;
  cout << "Duration of Sorting(in s): " << duration << " seconds "<< endl;
  cout << "Duration of Sorting(in ms): " << duration*1000 << " milliseconds "<< endl << endl;

  //--------MERGE SORT----------
  clock_t mergeStartTime = clock();
  mergeSort(mergeArr, 0, totalElements - 1);
  clock_t mergeEndTime = clock();
  double durationmerge = ((mergeEndTime - mergeStartTime)/(double)(CLOCKS_PER_SEC));//(double)(quickEndTime - quickStartTime);
  cout << "Sorting Algorithm: Merge Sort" << endl;
  cout << "Time Sort Started: " << mergeStartTime << endl;
  cout << "Time Sort Ended: " << mergeEndTime << endl;
  cout << "Duration of Sorting(in s): " << durationmerge << " seconds " << endl;
  cout << "Duration of Sorting(in ms): " << durationmerge*1000 << " milliseconds "<< endl << endl;

  //--------selction SORT----------
  clock_t selectionStartTime = clock();
  selectionSort(selectionArr, totalElements);
  clock_t selectionEndTime = clock();
  double durationselection = ((selectionEndTime - selectionStartTime)/(double)(CLOCKS_PER_SEC));//(double)(quickEndTime - quickStartTime);
  cout << "Sorting Algorithm: Selection Sort" << endl;
  cout << "Time Sort Started: " << selectionStartTime << endl;
  cout << "Time Sort Ended: " << selectionEndTime << endl;
  cout << "Duration of Sorting(in s): " << durationselection << " seconds " << endl;
  cout << "Duration of Sorting(in ms): " << durationselection*1000 << " milliseconds "<< endl << endl;

  //--------insertion SORT----------
  clock_t insertionStartTime = clock();
  insertionSort(insertionArr, totalElements);
  clock_t insertionEndTime = clock();
  double durationinsertion = ((insertionEndTime - insertionStartTime)/(double)(CLOCKS_PER_SEC));//(double)(quickEndTime - quickStartTime);
  cout << "Sorting Algorithm: Insertion Sort" << endl;
  cout << "Time Sort Started: " << insertionStartTime << endl;
  cout << "Time Sort Ended: " << insertionEndTime << endl;
  cout << "Duration of Sorting(in s): " << durationinsertion << " seconds " << endl;
  cout << "Duration of Sorting(in ms): " << durationinsertion*1000 << " milliseconds "<< endl << endl;

  //--------BUBBLE SORT----------
  clock_t bubbleStartTime = clock();
  bubbleSort(bubbleArr);
  clock_t bubbleEndTime = clock();
  double durationbubble = ((bubbleEndTime - bubbleStartTime)/(double)(CLOCKS_PER_SEC));//(double)(quickEndTime - quickStartTime);
  cout << "Sorting Algorithm: Bubble Sort" << endl;
  cout << "Time Sort Started: " << bubbleStartTime << endl;
  cout << "Time Sort Ended: " << bubbleEndTime << endl;
  cout << "Duration of Sorting(in s): " << durationbubble << " seconds " << endl;
  cout << "Duration of Sorting(in ms): " << durationbubble*1000 << " milliseconds "<< endl << endl;
}
