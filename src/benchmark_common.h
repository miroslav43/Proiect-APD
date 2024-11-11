//FILE: benchmark_common.h
#ifndef BENCHMARK_COMMON_H
#define BENCHMARK_COMMON_H

#define NUM_THREADS 10 // Adjust as needed
#define REPEATS 1000 // Adjust as needed
#define WORKLOAD 1000 // Number of float additions

void do_work(int thread_id);

#endif // BENCHMARK_COMMON_H
