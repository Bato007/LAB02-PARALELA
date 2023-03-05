#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMEROS 100

void getNumbers(int * numeros, int * contador, char * linea);
void quickSort(int *numeros, int lo, int hi);

int main(){
    FILE *fp, *fptr;
    char linea[1000];
    int * numeros = NULL;
    int * contador =  malloc(sizeof(int)); 

    // Abrimos el archivo en el que se va a escribir los numeros ordenados y en donde vamos a leer los numeros
    fptr = fopen("numerosOrdenados.txt", "w");
    fp = fopen("numeros.txt", "r");
    if (fp == NULL && fptr == NULL){
        printf("Error!");
        exit(1);
    }


    fgets(linea, 1000, fp);

    // Se esta asignando la memoria para un entero cada entero
    numeros = (int *) malloc(1 * sizeof(int));
    if (numeros == NULL) {
        printf("Error al asignar memoria\n");
        exit(1);
    }
    getNumbers(numeros, contador, linea);
    quickSort(numeros, 0, *contador - 1);

    // Imprimimos los números almacenados en el array
    for (int i = 0; i < *contador; i++) {
        if (i < *contador - 1) 
            fprintf(fptr, "%d, ", numeros[i]);
        else 
            fprintf(fptr, "%d", numeros[i]);
        printf("%d ", numeros[i]);
    }
    printf("\n");

     
    // Cerramos los archivos
    fclose(fp);
    fclose(fptr);

    // Liberamos la memoria asignada al array
    free(numeros);
    free(contador);

    return 0;
}

void getNumbers(int * numeros, int * contador, char * linea){
    char * token;
    int tamano = 0;
    int cont = 0;

    token = strtok(linea, ",");
    while (token != NULL) {
        if (cont >= tamano) {
            tamano += 10;
            numeros = (int *) realloc(numeros, tamano * sizeof(int));
            if (numeros == NULL) {
                printf("Error al asignar memoria\n");
                exit(1);
            }
        }
        numeros[cont] = atoi(token); // Convertimos el token a número entero
        cont++;
        token = strtok(NULL, ",");
    }
    *contador = cont;
}

void quickSort(int *numeros, int lo, int hi)
{
    if(lo > hi) return;
    int l = lo;
    int h = hi;
    int p = numeros[(hi + lo)/2];

    while(l <= h){
        while((numeros[l] - p) < 0) l++;
        while((numeros[h] - p) > 0) h--;
        if(l<=h){
        //swap
        int tmp = numeros[l];
        numeros[l] = numeros[h];
        numeros[h] = tmp;
        l++; h--;
        }
    }
    //recursive call
    quickSort(numeros, lo, h);
    quickSort(numeros, l, hi);
}