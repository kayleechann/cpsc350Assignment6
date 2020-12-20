#include <fstream>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include "GenerateFile.h"

GenerateFile::GenerateFile(){
  //constructor
}

GenerateFile::~GenerateFile(){
  //destructor
}

/* toFile() is sed to open and populate a text file with random doubles
  if the program cannot open the file entered as a command line argument
*/
void GenerateFile::toFile(){
  int num = 0;
  ofstream file;
  cout << "How many random numbers do you want sorted:  " << endl;
  cin >> num;

  srand(time(NULL));
  file.open("randomNums.txt");
  file << num << endl;
  for(int i = 0; i < num; ++i){
    file << randNum() << endl;
  }
  file.close();
}

//generate random number in this range
double GenerateFile::randNum(){
  double min = 1.0;
  double max = 20000.0;
  return ((double)rand() / RAND_MAX) * (max - min) + min;
}
