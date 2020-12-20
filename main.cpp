#include "Sorting.h"
#include "GenerateFile.h"

int main(int argc, char **argv) {
  if(argc != 2){
    cout << "ERROR: not a valid number of command line argumnets! " << endl;
  }else if(argc == 2){
    Sorting s;
    string filename = argv[1];
    s.readFile(filename);
    //s.~Sorting();
  }
  return 0;
}
