#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "main.h"

// All of the user settings
#include "config.h"

int main(int argc, char *argv[])
{
    parseConfig();
    while (1) {
    }
    return 0;
}

// Returns the associated block based on the signal value
const block *getBlock(int signal)
{
    for (int i = 0; i < (sizeof(blocks) / sizeof(blocks[0])); i++) {
        if (blocks[i].signal == signal) {
            return &blocks[i];
        }
    }
    return NULL;
}

// Assign each block a sig handler
void parseConfig() {
    for (int i = 0; i < (sizeof(blocks) / sizeof(blocks[0])); i++) {
        initializeBlock(&blocks[i]);
    }
}

// Sets up the signal handeling for the given block
void initializeBlock(const block *current)
{
    printf("Initlizing block %s with signal %d\n", current->icon, current->signal);
    signal(current->signal, sighander);
}

// Signal handler
void sighander(int signal)
{
    const block *current = getBlock(signal);
    printf("Received signal for %s\n", current->icon);
}
