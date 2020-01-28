all:readfile sparsefile fork

readfile:readfile.c
	gcc -Wall -Werror readfile.c -o readfile

sparsefile:sparsefile.c
	gcc -Wall -Werror sparsefile.c -o sparsefile

fork:fork.c
	gcc -Wall -Werror fork.c -o fork 

.PHONY: clean
clean:
	rm readfile sparsefile fork
