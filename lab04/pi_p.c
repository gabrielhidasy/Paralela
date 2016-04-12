#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<pthread.h>


void *monte_carlo_pi(void *np) {
  unsigned int n = *(unsigned int *) np;
  long long unsigned int in = 0, i;
  double x, y, d;
  unsigned int r1 = (n+1) * (pthread_self()+2);
  unsigned int r2 = (n+2) * (pthread_self()+1);
  for (i = 0; i < n; i++) {
    r1 = rand_r(&r1);
    r2 = rand_r(&r2);
    x = ((r1 % 1000000)/500000.0)-1;
    y = ((r2 % 1000000)/500000.0)-1;
    d = ((x*x) + (y*y));
    if (d <= 1) in+=1;
  }
  // printf("in thread %lu: %llu\n", pthread_self(), in);
  pthread_exit((void *) in);
}

int main(void) {
  int num_threads;
  unsigned int n, i, npt;
  long long unsigned int in = 0, in_th = 0;
  double pi;
  long unsigned int duracao;
  struct timeval start, end;

  scanf("%d %u",&num_threads, &n);
  npt = n/num_threads;
  pthread_t *threads;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  threads = malloc(sizeof(pthread_t)*num_threads);

  gettimeofday(&start, NULL);
  for (i = 0; i < num_threads; i++) {
    pthread_create(&threads[i],&attr, monte_carlo_pi,(void *) &npt);
  }
  for (i = 0; i < num_threads; i++) {
    pthread_join(threads[i], (void *) &in_th);
    // printf("in main recovering thread %d: %llu\n", i, in_th);
    in += in_th;
  }
  gettimeofday(&end, NULL);

  duracao = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));

  // printf("n = %d in = %lld\n", n, in);
  pi = 4*in/((double)n);
  printf("%lf\n%lu\n",pi,duracao);

  return 0;
}
