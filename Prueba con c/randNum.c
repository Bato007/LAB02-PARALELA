#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printRandoms(FILE *fptr, int lower, int upper, int count);

int main()
{
	int lower = 0, upper = 100, count = 10000000;
    FILE *fptr;

    fptr = fopen("numeros.txt", "w");

    if(fptr == NULL){
        printf("Error!");
        exit(1);
    }

	srand(time(0));

	printRandoms(fptr, lower, upper, count);

    fclose(fptr);

	return 0;
}

void printRandoms(FILE *fptr, int lower, int upper, int count)
{
	int i;
	for (i = 0; i < count; i++) {
		int num = (rand() %
		(upper - lower + 1)) + lower;
        if (i < count - 1)
            fprintf(fptr, "%d, ", num);
        else 
            fprintf(fptr, "%d", num);
	}
}
