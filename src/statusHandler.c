#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Headers */
#include "structs.h"
#include "main.h"


/* Configuration */
const char *FOREGROUND_COLOR[3] = { "%{F", "}", "%{F-}" };
const char *BACKGROUND_COLOR[3] = { "%{B", "}", "%{B-}" };
const char *LINE_COLOR[3] = { "%{U", "}", "%{U-}" };
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

// Write blocks status to pipe
void writeStatus(block *blockToWrite)
{
    char *status;
    status = setAttribute(blockToWrite->status, BACKGROUND_COLOR, blockToWrite->bgColor);
    status = setAttribute(blockToWrite->status, FOREGROUND_COLOR, blockToWrite->fgColor);
    writeToPipe(status);
    free(status);
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
        return 1;
    }
    else {
        /* free(blockToUpdate->status); */
        blockToUpdate->status = result;
        return 0;
    }
}
