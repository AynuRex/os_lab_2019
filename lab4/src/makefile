CC=gcc
CFLAGS=-I. -I../../lab3/src -std=c99 -w
VPATH=~/Документы/os_lab_2019/lab3/src/ ~/Документы/os_lab_2019/lab4/src/
LAB3PATH=~/Документы/os_lab_2019/lab3/src/
all : utils.o find_min_max.o sum.o parallel_sum.o parallel_min_max.o parallel_sum parallel_min_max process_memory clean

parallel_min_max.o : $(LAB3PATH)parallel_min_max.c
	$(CC) -o $@ -c $(LAB3PATH)parallel_min_max.c $(CFLAGS)

parallel_min_max : $(LAB3PATH)utils.o $(LAB3PATH)find_min_max.o
	$(CC) -o $@ utils.o find_min_max.o parallel_min_max.o $(CFLAGS)

utils.o : $(LAB3PATH)utils.h $(LAB3PATH)utils.c
	$(CC) -o $@ -c $(LAB3PATH)utils.c $(CFLAGS)

find_min_max.o : $(LAB3PATH)utils.h $(LAB3PATH)find_min_max.h $(LAB3PATH)utils.c $(LAB3PATH)find_min_max.c
	$(CC) -o $@ -c $(LAB3PATH)find_min_max.c $(CFLAGS)

parallel_sum.o : parallel_sum.c sum.c sum.h
	$(CC) -o $@ -c parallel_sum.c $(CFLAGS)

sum.o : sum.c sum.h
	$(CC) -o $@ -c sum.c $(CFLAGS)

parallel_sum : parallel_sum.o $(LAB3PATH)utils.o $(LAB3PATH)find_min_max.o
	$(CC) -o $@ parallel_sum.c $(LAB3PATH)find_min_max.o $(LAB3PATH)utils.o sum.o $(CFLAGS) -lpthread

process_memory : process_memory.c
	$(CC) -o $@ process_memory.c -std=c99 -w

clean :
	rm utils.o find_min_max.o parallel_min_max.o parallel_sum.o sum.o

cleanAll :
	rm utils.o find_min_max.o parallel_min_max.o parallel_sum.o sum.o parallel_min_max parallel_sum process_memory text.txt