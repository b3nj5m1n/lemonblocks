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

void getBlockStatus(const block *current, char *status)
{
    // Icon
    if (current->icon != NULL) {
        strcat(status, current->icon);
    }
    strcat(status, DELIM_ICON);
    executeCommand(current, status);
    strcat(status, DELIM);
}

char *getStatus()
{
    char *result = malloc(( MAX_LEN + sizeof(DELIM) + sizeof(DELIM_ICON) ) * (sizeof(blocks) / sizeof(blocks[0])));
    for (int i = 0; i < (sizeof(blocks) / sizeof(blocks[0])); i++) {
        getBlockStatus(&blocks[i], result);
    }
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
    printf("Received signal for %s\n", current->icon);
    setStatus();
}
