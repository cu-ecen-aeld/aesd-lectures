all:readfile sparsefile

readfile:readfile.c
	gcc -Wall -Werror readfile.c -o readfile

sparsefile:sparsefile.c
	gcc -Wall -Werror sparsefile.c -o sparsefile

.PHONY: clean
clean:
	rm readfile
