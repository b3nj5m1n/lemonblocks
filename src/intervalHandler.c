#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Headers */
#include "structs.h"
#include "main.h"
#include "intervalHandler.h"

void startIntervalHandler(int highestInterval, block *blocks, int numOfBlocks, int ppid)
{
    // Enter endless loop
    while (1) {
        // Wait for 1 second, increase current interval until highest interval is reached, then repeat
        for (int i = 0; i < highestInterval; i++) {
            for (int j = 0; j < numOfBlocks; j++) {
                if (blocks[j].interval != 0 && i % blocks[j].interval == 0) {
                    printf("Reached interval %d for %s.\n", blocks[j].interval, blocks[j].icon);
                    kill(ppid, blocks[j].signal);
                }
            }
            sleep(1);
        }
    }
}
