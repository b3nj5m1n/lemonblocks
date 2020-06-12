#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include<sys/prctl.h>
#include<sys/wait.h>

#include "main.h"

// All of the user settings
#include "config.h"

// File descriptor for the pipe
int fd;
// Last written status
char *lStatus;

// Initlize the named pipe
void initPipe()
{
    // Path to named pipe used for IPC
    char *fifo = "/tmp/lemonblockspipe";
    // Make sure the pipe exists
    mkfifo(fifo, 0666);
    // Open fifo for writing
    fd = open(fifo, O_WRONLY);
}

// Close the connection to the pipe
void closePipe()
{
    close(fd);
}

void writeStatus(char *status)
{
    if (strcmp(lStatus, status) != 0) {
        write(fd, status, strlen(status));
        write(fd, "\n", 1);
        strcpy(lStatus, status);
    }
    else {
        printf("Nothing to do.\n");
    }
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    lStatus = malloc(sizeof(char) * MAX_LEN);
    parseConfig();
    initPipe();
    writeStatus("moin");
    writeStatus("Moiknasöodigh");
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
    writeStatus(current->icon);
}
