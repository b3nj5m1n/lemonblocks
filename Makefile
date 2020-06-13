# Makefile for lemonblocks

# Compiler + compiler/link flags
CC = gcc
CFLAGS = -c

# Input and output dirs
ODIR = obj
SDIR = src
LINK = -lpthread

# System bin dir
PREFIX?=/usr
BINDIR=${PREFIX}/bin

# Output binary
OUT = bin/lemonblocks

all: $(OUT)

$(OUT): main.o
	$(CC) $(ODIR)/main.o $(LINK) -o $(OUT)

main.o: src/main.c
	$(CC) $(CFLAGS) $(SDIR)/main.c -o $(ODIR)/main.o

install: $(OUT)
	install -D -m 755 ${OUT} ${BINDIR}/lemonblocks
	install -D -m 755 start-lemonbar.sh ${BINDIR}/start-lemonbar.sh
	install -D -m 755 test-scripts/* ${BINDIR}/

clean:
	rm -rf $(ODIR)/*.o

