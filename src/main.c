#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/prctl.h>
#include <signal.h>

/* This file starts 2 other processes and pipes results to lemonbar */

/* Headers */
#include "main.h"
#include "structs.h"
#include "configParser.h"
#include "signalHandler.h"
#include "intervalHandler.h"
#include "statusHandler.h"


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
    /* writeToPipe("\n"); */
    write(fd, "\n", 1);
}


int main(int argc, char *argv[])
{
    // How many blocks are there in total
    numOfBlocks = 0;
    // What is the highest interval in the config file
    int highestInterval = 0;
    // Parse the config into an array of block structs
    blocks = parseConfig(&numOfBlocks, &highestInterval);

    // Pid of current process to make sure only the parent process handles signals
    pid_t ppid = getpid();

    // Parse the array of blocks and generate a signal for every one, also set the pid of the process allowed to handle signals
    parseSignals(blocks, &numOfBlocks, ppid);

    // Loop over all blocks and update their status
    for (int i = 0; i < numOfBlocks; i++) {
        /* printf("Interval: %d, ", blocks[i].interval); */
        /* printf("Signal: %d, ", blocks[i].signal); */
        /* printf("Icon: %s, ", blocks[i].icon); */
        /* printf("Command: %s, ", blocks[i].command); */
        /* printf("Alignment: %c, ", blocks[i].alignment); */
        /* printf("Status: %s, ", blocks[i].status); */
        /* printf("Background Color: %s, ", blocks[i].bgColor); */
        /* printf("Foreground Color: %s, ", blocks[i].fgColor); */
        /* printf("\n"); */
        updateStatus(&blocks[i]);
    }

    // If there is at least one interval higher then zero, the interval handler is needed
    if (highestInterval > 0) {
        /* Create a new process for handeling the intervals */
        printf("Intervals are required, creating child process.\n");

        // Process for intervals
        if (fork() == 0)
        {
            // Make sure this process dies if the parent dies
            prctl(PR_SET_PDEATHSIG, SIGHUP);
            // Start the interval handler
            startIntervalHandler(highestInterval, blocks, numOfBlocks, ppid);
            exit(0);
        }
    }

    // Connect to the pipe
    connectToPipe();

    // Write the full inital status to the bar
    /* writeFullStatus(blocks, numOfBlocks); */

    while (1) {
        sleep(1);
    }

    return 0;
}
