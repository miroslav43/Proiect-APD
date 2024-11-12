#!/bin/bash

NUM_THREADS_LIST=(4 6 8 10)
REPEATS_LIST=(100 1000 10000)
NUM_RUNS=10 

PROGRAMS=("../bin/benchmark_pthread" "../bin/benchmark_barrier")

RESULT_FILE="average_time.csv"
echo "Program,Threads,Repeats,Average_Time(s)" > "$RESULT_FILE"

for PROGRAM in "${PROGRAMS[@]}"; do
    echo "Running benchmarks for $PROGRAM..."
    PROGRAM_NAME=$(basename "$PROGRAM")
    for NUM_THREADS in "${NUM_THREADS_LIST[@]}"; do
        for REPEATS in "${REPEATS_LIST[@]}"; do
            TIMES=()
            for ((i=1; i<=NUM_RUNS; i++)); do
                OUTPUT=$("./$PROGRAM" "$NUM_THREADS" "$REPEATS")
                if [ $? -ne 0 ]; then
                    echo "Error running $PROGRAM with $NUM_THREADS threads and $REPEATS repeats."
                    continue
                fi
                ELAPSED_TIME=$(echo "$OUTPUT" | tr -d '\r\n')
                TIMES+=("$ELAPSED_TIME")
            done
            SUM=0
            for TIME in "${TIMES[@]}"; do
                SUM=$(echo "$SUM + $TIME" | bc -l)
            done
            AVG_TIME=$(echo "$SUM / ${#TIMES[@]}" | bc -l)
            echo "$PROGRAM_NAME with $NUM_THREADS threads and $REPEATS repeats: Avg Time = $AVG_TIME seconds"
            echo "$PROGRAM_NAME,$NUM_THREADS,$REPEATS,$AVG_TIME" >> "$RESULT_FILE"
        done
    done
done
