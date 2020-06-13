#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<sys/prctl.h>
#include<sys/wait.h>

#include "main.h"

// All of the user settings
#include "config.h"

// File descriptor for the pipe
int fd;
/* // Last written status */
/* char *lStatus; */
// The highest interval
int maxInterval = 0;
// 1 if current process should handle signals
int signalHandler = 1;
int inpipefd[2];
// Contains the indicies of all right/center/left aligned modules
/* struct linkedInt { */
/*     int content; */
/*     struct linkedInt *next; */
/* }; */
/* struct linkedInt startRA; */
/* struct linkedInt startCA; */
/* struct linkedInt startLA; */
/* void appendInt(struct linkedInt *itemFromList, struct linkedInt *appendee) */
/* { */
/*     printf("fuuuuuuuuuuuuuuuuuuuuuuck"); */
/*     struct linkedInt *current = itemFromList; */
/*     while (current->next != NULL) */
/*     { */
/*         current = current->next; */
/*     } */
/*     current->next = itemFromList; */
/* } */

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
    /* if (strcmp(lStatus, status) != 0) { */
        write(fd, status, strlen(status));
        write(fd, "\n", 1);
    /* } */
    /* else { */
    /*     printf("Nothing to do.\n"); */
    /* } */
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
    /* lStatus = malloc(sizeof(char) * MAX_LEN); */
    // Parse Config
    parseConfig();

    // Pid of parent
    pid_t ppid;
    ppid = getpid();

    pipe(inpipefd);

    // Process for intervals
    if (fork() == 0)
    {
        printf("Started interval handler process.\n");
        dup2(inpipefd[0], STDIN_FILENO);
        signalHandler = 0;
        prctl(PR_SET_PDEATHSIG, SIGHUP);
        mainLoop(ppid);
        exit(0);
    }

    /* // Process for signals */
    /* if (fork() == 0) */
    /* { */
    /*     printf("Started signal handler process.\n"); */
    /*     prctl(PR_SET_PDEATHSIG, SIGHUP); */
    /*     signalHandler = 1; */
    /*     while (1) {} */
    /*     exit(0); */
    /* } */


    // Spawn new thread for handeling intervals
    /* pthread_t tid; */
    /* pthread_create(&tid, NULL, &mainLoop, NULL); */
    // Initialize pipe
    initPipe();
    while(1) {}
    /* writeStatus("moin"); */
    /* writeStatus("Moiknasöodigh"); */
    /* char *result = executeCommand(&blocks[0]); */
    /* printf("Command result: %s\n", result); */
    /* mainLoop(); */
    return 0;
}

// Is responsible for intervals
void *mainLoop(pid_t ppid)
{
    int counter = 0;
    while (1)
    {

        counter = (counter + 1) % (maxInterval + 1);
        if (counter == 0) { counter = 1; }
        printf("Counter %d\n", counter);

        int size = (sizeof(blocks) / sizeof(blocks[0]));
        for (int i = 0; i < size; i++) {
            int interval = blocks[i].interval;
            if (interval != 0 && counter % interval == 0) {
                printf("Interval for %s\n", blocks[i].icon);
                /* setBlockStatus(&blocks[i], i); */
                kill(ppid, blocks[i].signal);
                /* char *msg = "kill me"; */
                /* write(inpipefd[1], msg, strlen(msg)); */
            }
        }
        /* setStatus(); */
        sleep(1);
    }
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
        if (blocks[i].interval > maxInterval)
        {
            maxInterval = blocks[i].interval;
        }
    }
}


// Sets up the signal handeling for the given block
void initializeBlock(const block *current, int index)
{
    printf("Initlizing block %s with signal %d\n", current->icon, current->signal);
    signal(current->signal, sighandler);
    modules[index].status = malloc(sizeof(char)*MAX_LEN);
    // Align
    /* char *align = malloc(strlen(current->align)+5); */
    /* strcpy(align, "%{"); */
    /* if (strcmp(current->align, "") != 0) { */
    /*     strcat(align, current->align); */
    /* } else { */
    /*     strcat(align, "l"); */
    /* } */
    /* strcat(align, "}"); */
    /* modules[index].align = align; */
    /* struct linkedInt alignment; */
    /* alignment.content = index; */
    /* printf("i don't want to live on this planet anymore\n"); */
    /* if (strcmp(current->align, "r") == 0) { appendInt(&startRA, &alignment); printf("1\n"); } */
    /* else if (strcmp(current->align, "c") == 0) { appendInt(&startCA, &alignment); printf("1\n"); } */
    /* else if (strcmp(current->align, "l") == 0) { appendInt(&startLA, &alignment); printf("1\n"); } */
    /* printf("byyyee have a great time\n"); */
    // Foreground color
    char *fC = malloc(strlen(current->fgColor)+5);
    strcpy(fC, "%{F");
    if (strcmp(current->fgColor, "") != 0) {
        strcat(fC, current->fgColor);
    } else {
        strcat(fC, "-");
    }
    strcat(fC, "}");
    modules[index].fgColor = fC;
    // Background color
    char *bC = malloc(strlen(current->bgColor)+5);
    strcpy(bC, "%{B");
    if (strcmp(current->bgColor, "") != 0) {
        strcat(bC, current->bgColor);
    } else {
        strcat(bC, "-");
    }
    strcat(bC, "}");
    modules[index].bgColor = bC;
    setBlockStatus(current, index);
}

// Execute command for block and set status for that block
void setBlockStatus(const block *current, int index)
{
    char *status = malloc(sizeof(char)*MAX_LEN);
    strcpy(status, "");
    /* strcat(status, modules[index].align); */
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
    /* strcpy(modules[index].status, status); */
    modules[index].status = status;
}

void getStatus(char *result)
{
    strcpy(result, "");
    char prevAlign = ' ';
    for (int i = 0; i < (sizeof(blocks) / sizeof(blocks[0])); i++) {
        if (prevAlign != blocks[i].align) {
            strcat(result, "%{");
            strcat(result, &blocks[i].align);
            strcat(result, "}");
        }
        strcat(result, modules[i].status);
        printf("Status: %s\n", modules[i].status);
        prevAlign = blocks[i].align;
    }
}

void setStatus()
{
    char *status = (char *) malloc(MAX_LEN*100);
    getStatus(status);
    writeStatus(status);
    /* free(lStatus); */
    /* lStatus = (char *) malloc(MAX_LEN*100); */
    /* strcpy(lStatus, status); */
    /* free(status); */
    /* lStatus = status; */
}

// Signal handler
void sighandler(int signal)
{
    if (signalHandler == 1)
    {
        const block *current = getBlock(signal);
        int index = getBlockIndex(signal);
        printf("Received signal for %s\n", current->icon);
        setBlockStatus(current, index);
        setStatus();
    }
}
