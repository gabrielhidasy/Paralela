#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
struct minmax_args {
  double *v;
  int n;
};
struct args_hist {
  double *v;
  int n;
  int bins_i;
  double bins_s;
  int bins_n;
};
struct minmax {
  double min,max;
};
void *minmax_t(void *args);
void *countElPerBin(void *args);

int main() {
  int num_threads;
  struct timeval start,end;
  int n, bins;
  double *vet;
  int i;
  scanf("%d %d %d",&num_threads,&n,&bins);
  vet = malloc(sizeof(double)*n);
  pthread_t *threads;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  threads = malloc(sizeof(pthread_t)*num_threads);
  for (i=0;i<n;i++) scanf("%lf",&vet[i]);
  int *binsvet = malloc(sizeof(int)*bins);
  int *binsvettmp = NULL;
  for (i=0;i<bins;i++) binsvet[i] = 0;
  struct minmax_args *a = malloc(sizeof(struct minmax_args)*num_threads);
  struct minmax *b;


  gettimeofday(&start,NULL);
  for (i=0;i<num_threads;i++) {
    a[i].v = vet+(i*n/num_threads);
    a[i].n=n/num_threads;
  }
  for (i=0;i<num_threads;i++) {
    pthread_create(&threads[i],&attr,minmax_t,(void *) &a[i]);
  }
  double min=10000000,max=-100000000;
  for (i=0;i<num_threads;i++) {
    pthread_join(threads[i],(void *) &b);
    if(min>b->min) min=b->min;
    if(max<b->max) max=b->max;
    free(b);
  }
  max = ceil(max);
  min = floor(min);
  double x = max-min;
  double steep = (x/bins);
  //printf("%lf %lf %lf %d max min steep bins\n",max,min,steep,bins);
  struct args_hist *args;
  args = malloc(sizeof(struct args_hist)*num_threads);
  for (i=0;i<bins;i++) printf("%.2lf ",(double) (min+i*steep));
  printf("%.2lf\n",(double) (min+i*steep));
  for (i=0;i<num_threads;i++) {
    args[i].v = vet+(n/num_threads)*i;
    args[i].n = n/num_threads;
    args[i].bins_s = steep;
    args[i].bins_n = bins;
    args[i].bins_i = min;
  }
  for (i=0;i<num_threads;i++)
    pthread_create(&threads[i],&attr,countElPerBin, (void *) &args[i]);
  int y;
  for (i=0;i<num_threads;i++) {
    pthread_join(threads[i],(void *) &binsvettmp);
    for (y=0;y<bins;y++) binsvet[y]+=binsvettmp[y];
  }
  gettimeofday(&end,NULL);
  for (i=0;i<bins-1;i++) printf("%d ",binsvet[i]);
  printf("%d\n",binsvet[i]);
  printf("%ld\n",(end.tv_sec*1000000+end.tv_usec)-(start.tv_sec*1000000+start.tv_usec));
  free(binsvet);
  free(threads);
  free(a);
  free(vet);
  return 0;

}
void *minmax_t(void *args) {
  struct minmax_args *a;
  a = args;
  double *v = a->v;
  int n = a->n;
  int i;
  double max=-10000,min=1<<30;
  for (i=0;i<n;i++) {
    if(v[i]>max) max=v[i];
    if(v[i]<min) min=v[i];
  }
  struct minmax *ret = malloc(sizeof(struct minmax));
  ret->min=min;
  ret->max=max;
  pthread_exit((void*) ret);
}
void *countElPerBin(void *args) {
  struct args_hist *tmp = (struct args_hist *) args;
  int init = tmp->bins_i;
  double steep = tmp->bins_s;
  int bins_n = tmp->bins_n;
  double *v = tmp->v;
  int n = tmp->n;
  int i;
  int *bins = malloc(sizeof(int)*(tmp->bins_n));
  for (i=0;i<bins_n;i++) bins[i]=0;
  for (i=0;i<n;i++)
    bins[((int) ceil(((v[i]-init)/steep)))-1]++;
  pthread_exit((void *) bins);
}

/*
|         | Threads    | 1 |    2 |    4 |     8 |    16 |
| arq1.in | Speedup    | 1 | 0.89 | 0.75 |  0.42 |  0.24 |
|         | Eficiência | 1 | 0.45 | 0.19 |  0.05 | 0.015 |
| arq2.in | Speedup    | 1 | 1.13 | 1.07 |  0.90 |  0.66 |
|         | Eficiência | 1 | 0.56 | 0.26 | 0.125 |  0.04 |
| arq3.in | Speedup    | 1 | 1.79 | 2.88 |  2.14 |  2.06 |
|         | Eficiência | 1 | 0.89 | 0.72 |  0.27 |  0.13 |

Como o programa foi testado em uma maquina quad-core, era esperado que
a eficiência não iria melhorar nada com mais threads.

O arquivo 1 continha uma entrada muito pequena, é difícil conseguir algum
speed-up nesse caso

Não consegui usar o gprof com nenhuma das entradas, a execução termina rápido
demais, ele não registra nada
*/
