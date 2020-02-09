all:segfaulter signal_handler time_functions sleep_functions timer_simple timer_thread

CC=$(CROSS_COMPILE)gcc
# use the -g flag to include debug info so our core file has line numbers
CCFLAGS=-Wall -Werror -g

segfaulter:segfaulter.c
	$(CC) $(CCFLAGS) segfaulter.c -o segfaulter

signal_handler:signal_handler.c
	$(CC) $(CCFLAGS) signal_handler.c -o signal_handler

time_functions:time_functions.c time_functions_shared.h
	$(CC) $(CCFLAGS) time_functions.c -o time_functions

sleep_functions:sleep_functions.c sleep_args.h time_functions_shared.h sleep_args.c sleep_args.h
	$(CC) $(CCFLAGS) sleep_functions.c sleep_args.c -o sleep_functions 

timer_simple:timer_simple.c
	$(CC) $(CCFLAGS) timer_simple.c -o timer_simple

timer_thread:timer_thread.c time_functions_shared.h
	$(CC) $(CCFLAGS) timer_thread.c -o timer_thread -lrt -pthread


.PHONY: clean
clean:
	rm -f segfaulter signal_handler sleep_functions timer_simple timer_thread
