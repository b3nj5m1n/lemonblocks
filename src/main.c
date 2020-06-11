#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include<sys/prctl.h>
#include<sys/wait.h>

#include "main.h"

// All of the user settings
#include "config.h"

// Stdin pipe
int inpipefd[2];
// Stdout pipe
int outpipefd[2];
char buf[256];
char msg[256] = "moin";

// Last written status
char *lStatus;

// Spawns lemonbar
void lemonbar()
{
    // Pid will be changed to the pid of the child process (lemonbar)
    pid_t pid = 0;
    int status;

    // Create new pipes
    pipe(inpipefd);
    pipe(outpipefd);
    // Fork this process
    pid = fork();
    // If this is not the original process
    if (pid == 0)
    {
        // Set pipes
        dup2(outpipefd[0], STDIN_FILENO);
        dup2(inpipefd[1], STDOUT_FILENO);
        /* dup2(inpipefd[1], STDERR_FILENO); */

        // Send signal to parent if this process dies
        prctl(PR_SET_PDEATHSIG, SIGTERM);

        execl("/usr/local/bin/bar", "-p -f 'UbuntuMono Nerd Font' -f 'Twemoji'", (char*) NULL);
        exit(1);
    }
    //close unused pipe ends
    close(outpipefd[0]);
    close(inpipefd[1]);

    /* while(1) */
    /* { */
    /*     write(outpipefd[1], msg, strlen(msg)); */
    /*     read(inpipefd[0], buf, 256); */
    /* } */

    /* kill(pid, SIGKILL); //send SIGKILL signal to the child process */
    /* waitpid(pid, &status, 0); */
}

void writeStatus(char *status)
{
    if (strcmp(lStatus, status) != 0) {
        write(outpipefd[1], status, strlen(status));
        write(outpipefd[1], "\n", 1);
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
    lemonbar();
    writeStatus("Moin");
    writeStatus("Moin2");
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
