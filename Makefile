# Makefile for lemonblocks

# Compiler + compiler/link flags
CC = gcc
CFLAGS = -c

# Input and output dirs
ODIR = obj
SDIR = src

# Output binary
OUT = bin/lemonblocks

all: $(OUT)

$(OUT): main.o
	$(CC) $(ODIR)/main.o -o $(OUT)

main.o: src/main.c
	$(CC) $(CFLAGS) $(SDIR)/main.c -o $(ODIR)/main.o

clean:
	rm -rf $(ODIR)/*.o

