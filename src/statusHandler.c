#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Headers */
#include "structs.h"
#include "main.h"
#include "statusHandler.h"


/* Configuration */
char *DELIMITER = "  ";
char *ICON_DELIMITER = " ";
const char *FOREGROUND_COLOR[3] = { "%{F#", "}", "%{F-}" };
const char *BACKGROUND_COLOR[3] = { "%{B#", "}", "%{B-}" };
const char *LINE_COLOR[3] = { "%{U#", "}", "%{U-}" };
const char *LEFT_CLICK[3] = { "%{A1:", ":}", "%{A1}" };
const char *MIDDLE_CLICK[3] = { "%{A2:", ":}", "%{A2}" };
const char *RIGHT_CLICK[3] = { "%{A3:", ":}", "%{A3}" };
const char *SCROLL_UP_CLICK[3] = { "%{A4:", ":}", "%{A4}" };
const char *SCROLL_DOWN_CLICK[3] = { "%{A5:", ":}", "%{A5}" };



// Returns pointer to string surrounded by two other strings
char *surround(char *stringToSurround, char *surrounderOne, char *surrounderTwo)
{
    // Allocate memeory for return value
    char *result = malloc(strlen(stringToSurround) + strlen(surrounderOne) + strlen(surrounderTwo));
    strcpy(result, "");
    // Add surrounder one
    strcat(result, surrounderOne);
    // Add string to surround
    strcat(result, stringToSurround);
    // Add surrounder two
    strcat(result, surrounderTwo);
    return result;
}

/* attributeConfig should be one of the arrays from the configuration section above */
/* attributeContent should be what you want to set the attribute to, for example #ff0066 */
/* content should be the string you want to set that attribute for */
char *setAttribute(char *content, const char **attributeConfig, char *attributeContent)
{
    // Allocate memeory for return value
    char *result = malloc(strlen(content) + strlen(attributeContent) + strlen(attributeConfig[0]) + strlen(attributeConfig[1]) + strlen(attributeConfig[2]));
    strcpy(result, "");
    strcat(result, attributeConfig[0]);
    strcat(result, attributeContent);
    strcat(result, attributeConfig[1]);
    strcat(result, content);
    strcat(result, attributeConfig[2]);
    return result;
}

// Write status for all blocks to pipe
void writeFullStatus(block *blocks, int numOfBlocks)
{
    // Flush pipe to begin with
    /* flushPipe(); */

    // Variable for status to write
    char *status = malloc(sizeof(char) * numOfBlocks * 2048);
    strcpy(status, "\n");

    // Keep track of alignment
    char *alignment = " ";
    // Loop over all blocks
    for (int i = 0; i < numOfBlocks; i++) {
        // If the alignment changed, write the new one to the pipe
        if (strcmp(alignment, blocks[i].alignment) != 0) {
            strcat(status, "%{");
            strcat(status, blocks[i].alignment);
            strcat(status, "}");
        } else {
            // The alignment didn't change, so write the delimiter first
            strcat(status, DELIMITER);
        }

        // Write prefix
        strcat(status, blocks[i].prefix);

        // Write the icon for the current block
        strcat(status, blocks[i].icon);
        // Write the icon delimiter
        strcat(status, ICON_DELIMITER);
        // Write the status for the current block to the pipe
        strcat(status, blocks[i].status);

        // Change the alignment to the alignment of the current block
        alignment = blocks[i].alignment;

        // Write suffix
        strcat(status, blocks[i].suffix);
    }
    /* printf("%s\n", status); */
    /* strcat(status, "\n"); */
    writeToPipe(status);
    free(status);
    // Flush the pipe to see the new changes in the bar
    /* flushPipe(); */
}

// Run the associated command and update the status, return 0 if the status has changed
int updateStatus(block *blockToUpdate)
{
    // Variable to store the result in for comparison
    char *result = malloc(1024);
    // Run the command
    FILE *cmd;
    cmd = popen(blockToUpdate->command, "r");
    if (cmd == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    fgets(result, 1024, cmd);
    pclose(cmd);
    // Compare strings
    if (strcmp(result, blockToUpdate->status) == 0) {
        // The status hasn't changed since the last call
        free(result);
        return 1;
    }
    else {
        blockToUpdate->status = result;
        return 0;
    }
}
