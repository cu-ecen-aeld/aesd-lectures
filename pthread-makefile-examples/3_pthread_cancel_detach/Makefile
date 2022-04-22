# Makefile Tutorial 3: Automatic Variables, Pattern Rule
# Reference: https://riptutorial.com/makefile/example/21469/automatic-variables

# 				Automatic Variables
# Within the context of an individual rule, Make automatically defines a number of special variables.
# These variables can have a different value for each rule in a makefile and are designed to make writing rules simpler.
# These variables can only be used in the recipe portion of a rule.
# Below is a table of a few automatic variables and their description,
# 
# $@ :- File name of the rule's target
# $< :- File name of the first pre-requisite (or dependency) in the list of dependencies mentioned in rule
# $^ :- List all pre-requisites
# $? :- List of all pre-requisites that are newer than the target

#				Pattern rules
# You define an implicit rule by writing a pattern rule.
# When make wants to build a target, if there's no explicit rule for the target, 
# then it will go through the dictionary of pattern rules to find a rule that will build the target.

# NOTE: This make file is used to generate an executable file for every source file (.c) in this directory

CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS = -lpthread

# "$(basename $(wildcard *.c))" returns the file names of .c files without extension
# This is in turn being used as dependencies for the target all.

all: $(basename $(wildcard *.c))

# Here, the target pattern is % which will match anything (the % is a wildcard, kind of like the shell's * globbing character).
# So every target make wants to build will match this pattern.
# Then make looks to see if the prerequisite exists or can be built, replacing the stem (the text that matches %) in the prerequisite(s).

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

.PHONY: clean

clean: 
	rm -rf $(basename $(wildcard *.c))