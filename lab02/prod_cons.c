#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
long long unsigned int producer_consumer(int **buffer, int size, int *vec, int n);

int main()
{
  int num_threads;
  int num_cycles;
  int buffer_size;
  unsigned long long int sum = 0;
  int i = 0;
  int y = 0;

  scanf("%d %d %d",&num_threads,&num_cycles,&buffer_size);

#ifdef SERIAL
  num_threads = 1;
#endif

  /* Allocate buffers, one for each thread */
  int **buffer = malloc(sizeof(int*)*num_threads);
  for (i = 0; i < num_threads; i++) {
    buffer[i] = malloc(sizeof(int)*buffer_size);
    for (y = 0; y < buffer_size; y++) {
      buffer[i][y] = 0;
    }
  }

  omp_set_num_threads(num_threads);

  /* Read input */
  int *vec = malloc(sizeof(int) * num_cycles);
  for (i=0; i<num_cycles;i++) {
    scanf("%d", &vec[i]);
  }

  /* Calculete results */
  double start = omp_get_wtime();
  sum = producer_consumer\
    (buffer, buffer_size, vec, num_cycles);

  for (i=0; i < num_threads; i++) {
    free(buffer[i]);
  }
  free(vec);
  free(buffer);
  printf("%lld\n%lf\n",sum,omp_get_wtime()-start);
}

long long unsigned int producer_consumer              \
(int **buffer, int size, int *vec, int n)
{
  int i, j;
  long long unsigned int sum = 0;
#ifndef SERIAL
#pragma omp parallel for private(j) reduction(+: sum) schedule(static, 2)
#endif
  for(i=0;i<n;i++) {
    int tid = omp_get_thread_num();
    /* PRODUTOR */
    if (i % 2 == 0) {
      for(j=0;j<size;j++) {
      buffer[tid][j] = vec[i] + j*vec[i+1];
    }
  }
    else {
    /* CONSUMIDO */
      for(j=0;j<size;j++) {
        sum += buffer[tid][j];
      }
    }
  }
  return sum;
}

    /*************************************************************
/proc/cpuinfo:
Its a dual-core, hyperthread-enabled core i5, first generation, M520
gabriel@localhost $ cat /proc/cpuinfo
processor	: 0
vendor_id	: GenuineIntel
cpu family	: 6
model		: 37
model name	: Intel(R) Core(TM) i5 CPU       M 520  @ 2.40GHz
stepping	: 5
microcode	: 0x4
cpu MHz		: 1199.000
cache size	: 3072 KB
physical id	: 0
siblings	: 4
core id		: 0
cpu cores	: 2
apicid		: 0
initial apicid	: 0
fpu		: yes
fpu_exception	: yes
cpuid level	: 11
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 cx16 xtpr pdcm pcid sse4_1 sse4_2 popcnt aes lahf_lm ida arat dtherm tpr_shadow vnmi flexpriority ept vpid
bugs		:
bogomips	: 4790.71
clflush size	: 64
cache_alignment	: 64
address sizes	: 36 bits physical, 48 bits virtual
power management:

processor	: 1
vendor_id	: GenuineIntel
cpu family	: 6
model		: 37
model name	: Intel(R) Core(TM) i5 CPU       M 520  @ 2.40GHz
stepping	: 5
microcode	: 0x4
cpu MHz		: 1199.000
cache size	: 3072 KB
physical id	: 0
siblings	: 4
core id		: 0
cpu cores	: 2
apicid		: 1
initial apicid	: 1
fpu		: yes
fpu_exception	: yes
cpuid level	: 11
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 cx16 xtpr pdcm pcid sse4_1 sse4_2 popcnt aes lahf_lm ida arat dtherm tpr_shadow vnmi flexpriority ept vpid
bugs		:
bogomips	: 4790.71
clflush size	: 64
cache_alignment	: 64
address sizes	: 36 bits physical, 48 bits virtual
power management:

processor	: 2
vendor_id	: GenuineIntel
cpu family	: 6
model		: 37
model name	: Intel(R) Core(TM) i5 CPU       M 520  @ 2.40GHz
stepping	: 5
microcode	: 0x4
cpu MHz		: 1199.000
cache size	: 3072 KB
physical id	: 0
siblings	: 4
core id		: 2
cpu cores	: 2
apicid		: 4
initial apicid	: 4
fpu		: yes
fpu_exception	: yes
cpuid level	: 11
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 cx16 xtpr pdcm pcid sse4_1 sse4_2 popcnt aes lahf_lm ida arat dtherm tpr_shadow vnmi flexpriority ept vpid
bugs		:
bogomips	: 4790.71
clflush size	: 64
cache_alignment	: 64
address sizes	: 36 bits physical, 48 bits virtual
power management:

processor	: 3
vendor_id	: GenuineIntel
cpu family	: 6
model		: 37
model name	: Intel(R) Core(TM) i5 CPU       M 520  @ 2.40GHz
stepping	: 5
microcode	: 0x4
cpu MHz		: 1199.000
cache size	: 3072 KB
physical id	: 0
siblings	: 4
core id		: 2
cpu cores	: 2
apicid		: 5
initial apicid	: 5
fpu		: yes
fpu_exception	: yes
cpuid level	: 11
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 cx16 xtpr pdcm pcid sse4_1 sse4_2 popcnt aes lahf_lm ida arat dtherm tpr_shadow vnmi flexpriority ept vpid
bugs		:
bogomips	: 4790.71
clflush size	: 64
cache_alignment	: 64
address sizes	: 36 bits physical, 48 bits virtual
power management:
    **********************************************************/

    /********************************************************
gprof output
each sample hit covers 2 byte(s) for 1.07% of 0.94 seconds

index % time    self  children    called     name
                0.94    0.00    5000/5000        main [2]
[1]    100.0    0.94    0.00    5000         producer_consumer [1]
-----------------------------------------------
                                                 <spontaneous>
[2]    100.0    0.00    0.94                 main [2]
                0.94    0.00    5000/5000        producer_consumer [1]
-----------------------------------------------

The producer_consumer function takes most of the time
    ************************************************************/

    /*********************************************************
Flags de otimização (Testei com o arq3.in, já que é o maior)

Na versão serial
Sem flag (equivale a O0): 4.9s
-O0: 4.8s, sem speedup já que é o mesmo nivel
-O1: 1.4s, speedup de 3.42
-O2: 1.4s, speedup de 3.42
-O3: 1.17s, speedup de  4.10

Na versão paralela
-O0 = Sem flags: 2.5s
-O1: 0.92s, speedup de 2.71
-O2: 0.90s, speedup de 2.77
-O3: 0.76s, speedup de 3.29
Ainda há ganhos
    ***********************************************************/
