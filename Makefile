BINFOLDER := bin/
INCFOLDER := inc/
SRCFOLDER := src/
OBJFOLDER := obj/
TESTFOLDER := test/

CC := gcc
CFLAGS := -Wall -lpthread

SRCFILES := $(wildcard $(SRCFOLDER)*.c)

all: $(SRCFILES:src/%.c=obj/%.o)
	$(CC) $(CFLAGS) obj/controller.o obj/mq_utils.o obj/shm_utils.o obj/menu.o -o bin/controller_bin -I$(INCFOLDER)
	$(CC) $(CFLAGS) obj/sensor_simulator.o obj/mq_utils.o obj/shm_utils.o obj/menu.o -o bin/sensor_simulator_bin -I$(INCFOLDER)
	$(CC) $(CFLAGS) obj/instrument_cluster.o obj/mq_utils.o obj/shm_utils.o obj/menu.o -o bin/instrument_cluster_bin -I$(INCFOLDER)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I./inc

.PHONY: clean
clean:
	rm -rf obj/*
	rm -rf bin/*

run:
	bin/controller_bin

.SILENT: test
test: ./test/test_shm_utils test/test_mq_utils ./test/test_mq_utils_read
	./test/test_mq_utils
	./test/test_mq_utils_read
	./test/test_shm_utils

test/test_mq_utils: test/test_mq_utils.c src/mq_utils.c test/unity.c
	$(CC) $(CFLAGS) test/test_mq_utils.c src/mq_utils.c test/unity.c -o test/test_mq_utils -I$(TESTFOLDER) -I$(INCFOLDER)

test/test_mq_utils_read: test/test_mq_utils_read.c src/mq_utils.c test/unity.c
	$(CC) $(CFLAGS) test/test_mq_utils_read.c src/mq_utils.c test/unity.c -o test/test_mq_utils_read -I$(TESTFOLDER) -I$(INCFOLDER)

test/test_shm_utils: test/test_shm_utils.c src/shm_utils.c test/unity.c
	$(CC) $(CFLAGS) test/test_shm_utils.c src/shm_utils.c test/unity.c -o test/test_shm_utils -I$(TESTFOLDER) -I$(INCFOLDER)
