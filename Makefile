
CC = gcc
CFLAGS = -Wall -O2 -I$(SRC_DIR)
LDFLAGS = -lpthread
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(BIN_DIR))

BARRIER_SRC = $(SRC_DIR)/barrier.c
DO_WORK_SRC = $(SRC_DIR)/do_work.c

BARRIER_HDR = $(SRC_DIR)/barrier.h
BENCHMARK_COMMON_HDR = $(SRC_DIR)/benchmark_common.h

BARRIER_OBJ = $(OBJ_DIR)/barrier.o
DO_WORK_OBJ = $(OBJ_DIR)/do_work.o

PROGRAMS = jones_family benchmark_pthread benchmark_barrier benchmark_test

all: $(PROGRAMS)

$(BARRIER_OBJ): $(BARRIER_SRC) $(BARRIER_HDR)
	$(CC) $(CFLAGS) -c $< -o $@

$(DO_WORK_OBJ): $(DO_WORK_SRC) $(BENCHMARK_COMMON_HDR)
	$(CC) $(CFLAGS) -c $< -o $@

jones_family: $(SRC_DIR)/jones_family.c $(BARRIER_OBJ)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@ $(LDFLAGS)

benchmark_pthread: $(SRC_DIR)/benchmark_pthread.c $(BARRIER_OBJ) $(DO_WORK_OBJ)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@ $(LDFLAGS)

benchmark_barrier: $(SRC_DIR)/benchmark_barrier.c $(BARRIER_OBJ) $(DO_WORK_OBJ)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@ $(LDFLAGS)

benchmark_test: $(SRC_DIR)/benchmark_test.c $(BARRIER_OBJ) $(DO_WORK_OBJ)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@ $(LDFLAGS)

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/*
