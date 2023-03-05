#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <vector>
#include "string"

#include "./generator.cpp"

using namespace std;

#define MAX_NUMEROS 100
#define DEFAULT_GENERATIONS 100
#define UNSORTED_FILE "./unsorted.txt"

int main(int argc, char* argv[]){
  int numsToGenerate = DEFAULT_GENERATIONS;
  string unsortFileName = UNSORTED_FILE;
  vector<int> numbers;
  string text;

  // if(argc > 1) {
  //   numsToGenerate = strtol(argv[1], NULL, 10);
  // }

  // generateNumbers(numsToGenerate, unsortFileName);

  ifstream unsortedFile(unsortFileName);
  // ofstream sortedFile(sortedFileName);

  while (getline(unsortedFile, text, ',')) {
    cout << text;
  }
  return 0;
}
