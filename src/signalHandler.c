#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* This file handles signals send to the program */

/* HEADERS */
#include "main.h"
#include "signalHandler.h"
#include "statusHandler.h"

block *sig_blocks;
int *sig_numOfBlocks;
int PID;

// Add signal for the given block
void addSignal(block *b)
{
    signal(b->signal, sighandler);
    printf("Added signal %d for block %s.\n", b->signal, b->icon);
}

// Set signals for all modules in the block array
void parseSignals(block *blocks_, int *numberOfBlocks_, int whitelistPID)
{
    sig_blocks = blocks_;
    sig_numOfBlocks = numberOfBlocks_;
    for (int i = 0; i < *sig_numOfBlocks; i++) {
        addSignal(&sig_blocks[i]);
    }
    PID = whitelistPID;
}

// Get the index associated with a signal
int getIndex(int signal)
{
    // Loop over all blocks
    for (int i = 0; i < *sig_numOfBlocks; i++) {
        // If the signal of the current block matches the argument return it
        if (sig_blocks[i].signal == signal) {
            return i;
        }
    }
    // There is no block associated with the signal
    return -1;
}

// Function executed when a signal is received
void sighandler(int signal)
{
    // Make sure only the parent process handles signals
    if (PID == getpid()) {
        // Get the index of the block for the received signal
        int index = getIndex(signal);
        printf("Received signal %d for block %s\n", signal, sig_blocks[index].icon);
        if (updateStatus(&sig_blocks[index]) == 0) {
            printf("Status has changed. New status: %s\n", sig_blocks[index].status);
        }
    }
}

