#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

int generateNumbers(int generate, string fileName) {
	int lower = 0, upper = 100;

  if (generate <= 0) {
    cout << "[ERROR] No numbers to generate" << endl;
    return -1;
  }

  ofstream unsorted(fileName);
	srand(time(0));

	for (int i = 0; i < generate; i++) {
		int num = (rand() % (upper - lower + 1)) + lower;

    unsorted << "" << num;
    if (i < generate - 1) {
      unsorted << ",";
    }
	}

  unsorted.close();
  cout << "Numbers generated" << endl;
  return 0;
}
