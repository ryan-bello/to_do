CC=gcc
CFLAGS=-I.
DEPS = goal_list.h date_and_time.h dynamic_arrays.h
OBJ = goal_list.o goal_list_func.o date_and_time.o dynamic_arrays.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

goal_list: $(OBJ)
	$(CC) -o goal_list goal_list.o goal_list_func.o date_and_time.o dynamic_arrays.o

run:
	./goal_list

run_goal_list:
	./goal_list

test:
	$(CC) -g -o goal_list goal_list.c goal_list_func.c dynamic_arrays.c date_and_time.c
