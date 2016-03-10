#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

double count_sort(double a[], int n);

int main() {
  int nThreads = 1;
  int nElems = 0;
  double *elems;
  scanf("%d", &nThreads);
  scanf("%d", &nElems);
  elems = malloc(sizeof(double)*nElems);
  int i = 0;
  for (int i = 0; i < nElems; i++) {
    scanf("%lf", &elems[i]);
  }
  double duration = 0;
  duration = count_sort(elems, nElems);
  for (i = 0; i < nElems; i++) {
    printf("%.2lf ", elems[i]);
  }
  printf("\n%lf\n", duration);
  return 0;
}

double count_sort(double a[], int n) {
  int i, j, count;
  double *temp;
  double start, end, duracao;

  temp = (double *)malloc(n*sizeof(double));

  start = omp_get_wtime();
  #pragma omp parallel for private(i, j, count)
  for (i = 0; i < n; i++) {
    count = 0;
    for (j = 0; j < n; j++)
      if (a[j] < a[i])
        count++;
      else if (a[j] == a[i] && j < i)
        count++;
    /* Critical unnecessary here, count never repeats */
    temp[count] = a[i];
  }
  end = omp_get_wtime();

  duracao = end - start;

  memcpy(a, temp, n*sizeof(double));
  free(temp);

  return duracao;
}
