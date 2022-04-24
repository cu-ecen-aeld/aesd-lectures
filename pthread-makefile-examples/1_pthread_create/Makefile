#Makefile Tutorial 1: Targets, Dependencies / Prerequisites, Recipes, Rules
#Reference: https://www.gnu.org/software/make/manual/html_node/Rule-Introduction.html

# Target: A target is usually the name of a file that is generated as a result of compilation; 
#	      examples of targets are executable or object files.
#		  A target can also be the name of an action to be carried out
#
# Dependencies: Dependencies are files that are used as inputs to create the target.
#
# Recipe: The recipe of a rule consists of one or more shell command lines to be executed, one at a time, 
#		  in the order they appear.
#
# Rules: A rule appears in the makefile and says when and how to remake certain files, 
#		 called the rule's targets (most often only one per rule).
#        It lists the other files that are the dependencies of the target, and commands to use to create,
#		 or update the target. 

all: pthread1 pthread2 #Here the target "all" has dependencies on the targets "pthread1" and "pthread2"

pthread1: 1_thread_create.c #The target "pthread1" depends on "1_thread_create". The below line represents the recipe to generate the target "pthread1"
	gcc 1_thread_create.c -o pthread1 -lpthread 

pthread2: 2_thread_create.c #The target "pthread2" depends on "2_thread_create". The below line represents the recipe to generate the target "pthread2"
	gcc 2_thread_create.c -o pthread2 -lpthread


clean:						#The target "clean" does not have any dependencies and it is used to delete the executable 
	rm -rf pthread1 pthread2