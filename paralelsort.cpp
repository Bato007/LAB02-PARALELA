#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <vector>
#include "string"

using namespace std;

#define N_THREADS 10
#define MAX_NUMEROS 100
#define DEFAULT_GENERATIONS 100
#define UNSORTED_FILE "./unsorted.txt"
#define SORTED_FILE "./sorted.txt"

void quickSort(vector<int> numeros[], int lo, int hi);

int main(int argc, char* argv[]){
  int n_threads=N_THREADS;
  string unsortFileName = UNSORTED_FILE;
  string sortedFileName = SORTED_FILE;
  vector<int> numbers;
  string text;  

  // Open files
  ifstream unsortedFile(unsortFileName);
  ofstream sortedFile(sortedFileName);

  while (getline(unsortedFile, text, ',')) {
    numbers.push_back(stoi(text));
  }

  int size = numbers.size() - 1;

  double t_init = omp_get_wtime();

  #pragma omp parallel num_threads(n_threads)
  {
    #pragma omp single
    quickSort(&numbers, 0, size);
  }
  double t_fin = omp_get_wtime();
  double delta = t_fin - t_init;
  cout << "Tiempo estimado = " << delta << endl;
  cout << "Para N = " << numbers.size() << endl;
  cout << "Para n_threads = " << n_threads << endl;

  // Imprimimos los números almacenados en el array
  if (numbers.size() > 0) {
    sortedFile << numbers.at(0);
    for (int i = 1; i < numbers.size(); i++) {
      sortedFile << "," << numbers.at(i);
    }
  }

  // Close files
  unsortedFile.close();
  sortedFile.close();

  return 0;
}

void quickSort(vector<int> numeros[], int lo, int hi)
{
  if(lo > hi) return;
  int l = lo;
  int h = hi;
  int p = numeros->at((hi + lo)/2);

  while(l <= h){
    while((numeros->at(l) - p) < 0) l++;
    while((numeros->at(h) - p) > 0) h--;
    if(l<=h){
      //swap
      int tmp = numeros->at(l);
      numeros->at(l) = numeros->at(h);
      numeros->at(h) = tmp;
      l++; h--;
    }
  }

  //recursive call
  #pragma omp task shared (numeros) if(h-lo > 1000) mergeable
  quickSort(numeros, lo, h);
  #pragma omp task shared (numeros) if(hi-l > 1000) mergeable
  quickSort(numeros, l, hi);
  #pragma omp taskwait
}