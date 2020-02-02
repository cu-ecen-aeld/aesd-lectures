all:withdraw_simple withdraw_threaded

withdraw_simple:withdraw_simple.c withdraw_shared.c
	gcc -Wall -Werror withdraw_simple.c withdraw_shared.c -o withdraw_simple

withdraw_threaded:withdraw_threaded.c withdraw_shared.c
	gcc -Wall -Werror -pthread withdraw_threaded.c withdraw_shared.c -o withdraw_threaded

.PHONY: clean
clean:
	rm withdraw_simple withdraw_threaded
