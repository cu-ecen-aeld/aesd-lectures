all:segfaulter signal_handler time_functions sleep_functions

segfaulter:segfaulter.c
	# use the -g flag to include debug info so our core file has line numbers
	gcc -Wall -Werror segfaulter.c -o segfaulter

signal_handler:signal_handler.c
	gcc -Wall -Werror signal_handler.c -o signal_handler

time_functions:time_functions.c time_functions_shared.h
	gcc -Wall -Werror time_functions.c -o time_functions

sleep_functions:sleep_functions.c sleep_args.h time_functions_shared.h sleep_args.c sleep_args.h
	gcc -Wall -Werror sleep_functions.c sleep_args.c -o sleep_functions 


.PHONY: clean
clean:
	rm -f segfaulter signal_handler sleep_functions
