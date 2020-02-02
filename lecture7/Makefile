all:withdraw_simple

withdraw_simple:withdraw_simple.c withdraw_shared.c
	gcc -Wall -Werror withdraw_simple.c withdraw_shared.c -o withdraw_simple

.PHONY: clean
clean:
	rm withdraw_simple
