all:segfaulter signal_handler

segfaulter:segfaulter.c
	# use the -g flag to include debug info so our core file has line numbers
	gcc -Wall -Werror segfaulter.c -o segfaulter

signal_handler:signal_handler.c
	gcc -Wall -Werror signal_handler.c -o signal_handler


.PHONY: clean
clean:
	rm segfaulter signal_handler
