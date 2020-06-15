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
	$(CC) $(ODIR)/* $(LINK) -o $(OUT)

main.o: src/main.c configParser.o signalHandler.o intervalHandler.o statusHandler.o
	$(CC) $(CFLAGS) $(SDIR)/main.c -o $(ODIR)/main.o
configParser.o: src/configParser.c
	$(CC) $(CFLAGS) $(SDIR)/configParser.c -o $(ODIR)/configParser.o
signalHandler.o: src/signalHandler.c
	$(CC) $(CFLAGS) $(SDIR)/signalHandler.c -o $(ODIR)/signalHandler.o
intervalHandler.o: src/intervalHandler.c
	$(CC) $(CFLAGS) $(SDIR)/intervalHandler.c -o $(ODIR)/intervalHandler.o
statusHandler.o: src/statusHandler.c
	$(CC) $(CFLAGS) $(SDIR)/statusHandler.c -o $(ODIR)/statusHandler.o

install: $(OUT)
	install -D -m 755 ${OUT} ${BINDIR}/lemonblocks
	install -D -m 755 start.sh ${BINDIR}/start-lemonbar.sh
	install -D -m 755 test-scripts/* ${BINDIR}/

config:
	mkdir ~/.config/lemonblocks/
	cp config.txt ~/.config/lemonblocks/

clean:
	rm -rf $(ODIR)/*.o

