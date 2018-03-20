# $Id$

SHELL:=/bin/bash
GCC=gcc
SRC=$(shell ls *.c )
OBJ=$(SRC:%.c=%.o)
BIN=$(SRC:%.c=%)

all: $(OBJ)

clean:
	rm -f *~ *.o $(BIN)

.SUFFIXES: .c .o

%.o: %.c
	-@$(GCC) -o $(basename $<) $<
