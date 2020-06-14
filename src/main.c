#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/* This file starts 2 other processes and pipes results to lemonbar */

/* Headers */
#include "main.h"
#include "structs.h"
#include "configParser.h"
#include "signalHandler.h"
#include "intervalHandler.h"


/* Constants */

// Path to the named pipe used by lemonbar
const char* fifo = "/tmp/lemonblockspipe";


/* Global Variables */

// File descriptor for named pipe used by lemonbar
int fd;
// Stores all of the blocks
block *blocks;
// How many blocks there are in total
int numOfBlocks;


// Connect to the named pipe used by lemonbar
void connectToPipe()
{
    // If the pipe doesn't already exist, create it
    if( access( fifo, F_OK ) == -1 ) {
        printf("Pipe doesn't exist, creating...\n");
        mkfifo(fifo, 0666);
    }
    // Open a connection to the pipe
    fd = open(fifo, O_WRONLY);
    // Test if the connection was established successfully
    if (fd == -1) {
        printf("Connection to pipe %s could not be established.\n", fifo);
        exit(1);
    }
}

// Close connection to named pipe
void closePipe()
{
    close(fd);
    printf("Closed connection to pipe %s.\n", fifo);
}

// Write something to the named pipe
void writeToPipe(char *buffer)
{
    write(fd, buffer, strlen(buffer));
}

// Write \n to pipe and refresh lemonbar
void flushPipe()
{
    writeToPipe("\n");
}


int main(int argc, char *argv[])
{
    numOfBlocks = 0;
    int highestInterval = 0;
    blocks = parseConfig(&numOfBlocks, &highestInterval);

    printf("Number of blocks: %d highest interval: %d\n", numOfBlocks, highestInterval);

    for (int i = 0; i < numOfBlocks; i++) {
        printf("Interval: %d, ", blocks[i].interval);
        printf("Signal: %d, ", blocks[i].signal);
        printf("Icon: %s, ", blocks[i].icon);
        printf("Command: %s, ", blocks[i].command);
        printf("Alignment: %c, ", blocks[i].alignment);
        printf("Status: %s, ", blocks[i].status);
        printf("\n");
    }

    parseSignals(blocks, &numOfBlocks);

    if (highestInterval > 0) {
        startIntervalHandler(highestInterval, blocks, numOfBlocks);
    }

    while (1) {
        sleep(1);
    }

    return 0;
}
