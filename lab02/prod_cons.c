#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
long long unsigned int producer_consumer(int *buffer, int size, int *vec, int n);
int main() {
  int num_threads;
  int num_ciclos;
  int buffer_size;
  unsigned long long int sum = 0;
  scanf("%d %d %d",&num_threads,&num_ciclos,&buffer_size);
  omp_set_num_threads(num_threads);
  int i=0;
  int **buffer = malloc(sizeof(int*)*((num_ciclos/2)+1));
  for(i=0;i<(1+num_ciclos/2);i++) {
    buffer[i] = malloc(sizeof(int)*buffer_size);
  }
  int *vec = malloc(sizeof(int)*num_ciclos);
  for(i=0; i<num_ciclos;i++)
    scanf("%d",&vec[i]);
  double start = omp_get_wtime();
  #ifndef SINGLE
  #pragma omp parallel for reduction(+: sum) schedule(static,1)
  #endif
  for(i=0;i<num_ciclos;i+=2) {
    sum+=producer_consumer\
      (buffer[i/2],buffer_size,&vec[i],1);
  }
  printf("%lld\n%lf\n",sum,omp_get_wtime()-start);
}

long long unsigned int producer_consumer\
(int *buffer, int size, int *vec, int n) {
	int j;
	long long unsigned int sum = 0;
        #ifndef SINGLE
	#pragma omp parallel for
	#endif
	  for(j=0;j<size;j++) {
	    buffer[j] = vec[0] + j*vec[1]; //produtor
	  }
	  #ifndef SINGLE
          #pragma omp parallel for reduction(+: sum)
	  #endif
	  for(j=0;j<size;j++)
	    sum+=buffer[j];
	return sum;
}

/*************************************************************
/proc/cpuinfo:
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
Sem flag (equivale a O0): 10.083824s
-O0: 10.124098s, sem speedup já que é o mesmo nivel
-O1: 3.205590s, speedup de 3.15826
-O2: 2.711301s, speedup de 3.73403
-O3: 2.031424s, speedup de 4.98374

Na versão paralela
-O0 = Sem flags: 5.834285
-O1: 2.06444, speedup de 2.82608
-O2: 1.98425, speedup de 2.94029
-O3: 1.16993, speedup de 4.98686
Ainda há ganhos, mas mais modestos em O1 e O2, e O3 teve um salto
maior dessa vez
***********************************************************/
