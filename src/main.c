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

typedef struct {
    char* fgColor;
    char* bgColor;
    char* status;
} module;
module *modules;

// Initlize the named pipe
void initPipe()
{
    // Path to named pipe used for IPC
    char *fifo = "/tmp/lemonblockspipe";
    // Make sure the pipe exists
    mkfifo(fifo, 0666);
    // Open fifo for writing
    fd = open(fifo, O_WRONLY);
    if (fd == -1)
    {
        printf("Connection to pipe could not be established.");
    }
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
        free(status);
    }
    else {
        printf("Nothing to do.\n");
    }
}

void executeCommand(const block *current, char *status)
{
    printf("Executing command.\n");
    FILE *cmd;
    /* Open the command for reading. */
    cmd = popen(current->command, "r");
    if (cmd == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    char *result = malloc(MAX_LEN);
    fgets(result, MAX_LEN, cmd);
    pclose(cmd);
    strcat(status, result);
    free(result);
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    lStatus = malloc(sizeof(char) * MAX_LEN);
    parseConfig();
    initPipe();
    /* writeStatus("moin"); */
    /* writeStatus("Moiknasöodigh"); */
    /* char *result = executeCommand(&blocks[0]); */
    /* printf("Command result: %s\n", result); */
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
// Returns the associated blocks index
int getBlockIndex(int signal)
{
    for (int i = 0; i < (sizeof(blocks) / sizeof(blocks[0])); i++) {
        if (blocks[i].signal == signal) {
            return i;
        }
    }
    return 0;
}

// Assign each block a sig handler
void parseConfig() {
    int size = (sizeof(blocks) / sizeof(blocks[0]));
    modules = malloc(sizeof(module)*size);
    for (int i = 0; i < size; i++) {
        initializeBlock(&blocks[i], i);
    }
}

// Sets up the signal handeling for the given block
void initializeBlock(const block *current, int index)
{
    printf("Initlizing block %s with signal %d\n", current->icon, current->signal);
    signal(current->signal, sighander);
    modules[index].status = malloc(sizeof(char)*MAX_LEN);
    // Foreground color
    char *fC = malloc(strlen(current->fgColor)+5);
    strcpy(fC, "%{F");
    strcat(fC, current->fgColor);
    strcat(fC, "}");
    modules[index].fgColor = fC;
    // Background color
    char *bC = malloc(strlen(current->bgColor)+5);
    strcpy(bC, "%{B");
    strcat(bC, current->bgColor);
    strcat(bC, "}");
    modules[index].bgColor = bC;
    setBlockStatus(current, index);
}

// Execute command for block and set status for that block
void setBlockStatus(const block *current, int index)
{
    char *status = malloc(sizeof(char)*MAX_LEN);
    strcpy(status, "");
    strcat(status, modules[index].fgColor);
    strcat(status, modules[index].bgColor);
    // Icon
    if (current->icon != NULL) {
        strcat(status, current->icon);
        strcat(status, DELIM_ICON);
    }
    executeCommand(current, status);
    strcat(status, "%{F-}%{B-}");
    strcat(status, DELIM);
    modules[index].status = status;
}

char *getStatus()
{
    char *result = malloc(sizeof(char)*MAX_LEN*10);
    strcpy(result, "");
    for (int i = 0; i < (sizeof(blocks) / sizeof(blocks[0])); i++) {
        strcat(result, modules[i].status);
    }
    printf("Status: %s\n", result);
    return result;
}

void setStatus()
{
    writeStatus(getStatus());
}

// Signal handler
void sighander(int signal)
{
    const block *current = getBlock(signal);
    int index = getBlockIndex(signal);
    printf("Received signal for %s\n", current->icon);
    setBlockStatus(current, index);
    setStatus();
}
