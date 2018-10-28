#include <stdio.h>
#include <omp.h>


void max(int*);

void min(int*);

void sum(int*);

void avg(int*);

static long ARRAY_SIZE = 1000;

void max(int* ar){
    int max = ar[0];
#pragma omp parallel for reduction(max: max)
    for (int i = 1; i < ARRAY_SIZE; ++i) {
        if (max<ar[i])
            max = ar[i];
    }

    printf("\nMax : %d", max);
}

void min(int *ar){
    int min = ar[0];
#pragma omp parallel for reduction(min: min)
    for (int i = 1; i < ARRAY_SIZE; ++i) {
        if (min>ar[i])
            min = ar[i];
    }

    printf("\nMin : %d", min);
}

void sum(int* ar){
    int sums = 0;
#pragma omp parallel for reduction(+: sums)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sums += ar[i];
    }

    printf("\nsum : %d", sums);
}

void avg(int* ar){
    int sum = 0;
#pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum+= ar[i];
    }

    printf("\navg : %f", (double)sum/ARRAY_SIZE);
}


int main ()
{
    int ar[ARRAY_SIZE];
    omp_set_num_threads(10);
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        ar[i] = i;
    }
    sum(ar);
    max(ar);
    min(ar);
    avg(ar);


    return 0;
}
