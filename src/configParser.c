#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <string.h>

/* Parses the config */

/* Headers */
#include "main.h"
#include "structs.h"
#include "configParser.h"
#include "signalHandler.h"

block *parseConfig(int *numOfBlocks, int *highestInterval)
{
    // Set locale to have utf-8 support
    if (!setlocale(LC_CTYPE, "")) {
      printf( "Can't set locale! Check LANG, LC_CTYPE, LC_ALL.\n");
      exit(1);
    }
    
    /* Count number of lines in config file */
    // Open config file
    FILE* file = fopen("config.txt", "r");
    // File will be read char by char, the current char will be stored in this variable
    char c;
    // Count number of lines in file
    while ((c = getc(file)) != EOF)
    {
        if (c == '\n') {
            *numOfBlocks = *numOfBlocks + 1;
        }
    }
    fclose(file);

    // Initialize array of blocks
    block *blocks = malloc(sizeof(block) * ( *numOfBlocks ));

    /* Parse config file */
    // Open config file
    file = fopen("config.txt", "r");

    // Variable to keep track of the current line
    int l = 0;

    // Read config file char by char until end of file
    while ((c = getc(file)) != EOF)
    {
        // Read one line of the file
        char *line = malloc(256);
        int n = 0;
        line[n] = c;
        while ((c = getc(file)) != '\n') {
            line[++n] = c;
        }
        // Declare new block
        block current;
        // Split the line into fields seperated by #
        char *field = malloc(256);
        // Interval
        field = strtok(line, "#");
        current.interval = atoi(field);
        if (current.interval > *highestInterval) {
            *highestInterval = current.interval;
        }
        // Signal
        field = strtok(NULL, "#");
        current.signal = atoi(field);
        // Icon
        field = strtok(NULL, "#");
        current.icon = field;
        if ( strcmp(current.icon, "NULL") == 0 ) { current.icon = ""; }
        // Command
        field = strtok(NULL, "#");
        current.command = field;
        // Alignment
        field = strtok(NULL, "#");
        current.alignment = field;
        // Status
        field = strtok(NULL, "#");
        current.status = field;
        // Background Color
        field = strtok(NULL, "#");
        current.bgColor = field;
        if ( strcmp(current.bgColor, "NULL") == 0 ) { current.bgColor = "-"; }
        // Foreground Color
        field = strtok(NULL, "#");
        current.fgColor = field;
        if ( strcmp(current.fgColor, "NULL") == 0 ) { current.fgColor = "-"; }

        blocks[l] = current;

        l++;
    }

    fclose(file);

    return blocks;
}

