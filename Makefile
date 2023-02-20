# Makefile
# Author: Clayton Brown
# Date: Feb 15, 2023
#
# COSC 3750, Homework 4
#
# This is just the Makefile used to compile the executable file
# which is named wycat. There is also a clean function that is
# used to remove th executable should the user wish to do so.

# Declare my variables
CC=gcc
CFLAGS=-Wall -ggdb -I.

# Declare my targets and PHONY's
targets: wycat
.PHONY: clean

# Compile the main executable
wycat: wycat.c
	$(CC) $(CFLAGS) wycat.c -o wycat

# Define the clean function
clean:
	/bin/rm -f "wycat"
