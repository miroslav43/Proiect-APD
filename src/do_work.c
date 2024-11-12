//FILE: benchmark_mybarrier.c
#include "benchmark_common.h"

void do_work(int thread_id) {
    float sum = 0.0f;
    for (int i = 0; i < WORKLOAD; i++) {
        sum += i * 0.0001f;
    }
    volatile float dummy = sum;
    (void)dummy;
}
