# Makefile Tutorial 2: Macros, PHONY Targets 	

#					Macros
# The make program allows you to use macros, which are similar to variables. 
# Macros are defined in a Makefile as = pairs. 
# Reference: https://www.star.nesdis.noaa.gov/pub/corp/scsb/wchen.RMAFTER-20190830/makefile_tutorial/makefile_macros.htm
# An example has been shown below −

CC = gcc # compiler macro
CFLAGS = -Wall -Werror  # Macro for compiler flags
LDFLAGS = -lpthread # Macro for linker flags

SRC_FILE = 1_threadjoin.c
TARGET = pthreadjoin

all: $(TARGET)

$(TARGET): $(SRC_FILE)
	$(CC) $(CFLAGS) $(SRC_FILE) -o $(TARGET) $(LDFLAGS)


# 								.PHONY Targets
# By default, Makefile targets are "file targets" - they are used to build files from other files.
# However, sometimes you want your Makefile to run commands that do not represent physical files in the file system. E.g: "clean"
# Chances are you may potentially have a file named clean
# In such a case, "clean" target would be associated with this file and make will only run the recipe when the file "clean" appears to be out of date
# These special targets are called phony and you can explicitly tell Make they're not associated with files

.PHONY: clean

clean:
	rm -rf $(TARGET)