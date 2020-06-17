#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

/* Parses the config */

/* Headers */
#include "main.h"
#include "structs.h"
#include "configParser.h"
#include "signalHandler.h"
#include "statusHandler.h"

block *parseConfig(int *numOfBlocks, int *highestInterval)
{
    // Set locale to have utf-8 support
    if (!setlocale(LC_CTYPE, "")) {
      printf( "Can't set locale! Check LANG, LC_CTYPE, LC_ALL.\n");
      exit(1);
    }
    
    /* Count number of lines in config file */
    // Get path to config file
    char *conffile = malloc(sizeof(char) * 100);
    strcpy(conffile, "");
    strcat(conffile, getpwuid(getuid())->pw_dir);
    strcat(conffile, "/.config/lemonblocks/config.txt");
    if( access( conffile, F_OK ) == -1 ) {
        printf("Could not find config file.\n");
        exit(1);
    }
    // Open config file
    FILE* file = fopen(conffile, "r");
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
    file = fopen(conffile, "r");

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
        field = strtok(line, ",");
        current.interval = atoi(field);
        if (current.interval > *highestInterval) {
            *highestInterval = current.interval;
        }
        // Signal
        field = strtok(NULL, ",");
        current.signal = atoi(field);
        // Icon
        field = strtok(NULL, ",");
        current.icon = field;
        if ( strcmp(current.icon, "NULL") == 0 ) { current.icon = ""; }
        // Command
        field = strtok(NULL, ",");
        current.command = field;
        // Alignment
        field = strtok(NULL, ",");
        current.alignment = field;
        // Status
        field = strtok(NULL, ",");
        current.status = field;
        // Background Color
        field = strtok(NULL, ",");
        current.bgColor = field;
        if ( strcmp(current.bgColor, "NULL") == 0 ) { current.bgColor = "-"; }
        // Foreground Color
        field = strtok(NULL, ",");
        current.fgColor = field;
        if ( strcmp(current.fgColor, "NULL") == 0 ) { current.fgColor = "-"; }
        // On left click
        field = strtok(NULL, ",");
        current.onLeftClick = field;
        // On middle click
        field = strtok(NULL, ",");
        current.onMiddleClick = field;
        // On right click
        field = strtok(NULL, ",");
        current.onRightClick = field;
        // On scroll up
        field = strtok(NULL, ",");
        current.onScrollUp = field;
        // On scroll down
        field = strtok(NULL, ",");
        current.onScrollDown = field;

        printf("l: %s; u: %s; d: %s\n", current.onLeftClick, current.onScrollUp, current.onScrollDown);

        // Generate pre & suffix
        current.prefix = malloc( strlen(current.onRightClick)+ strlen(current.onMiddleClick)+ strlen(current.onLeftClick)+ strlen(current.onScrollDown)+ strlen(current.onScrollUp));
        strcpy(current.prefix, "");
        // Colors
        if (strcmp(current.fgColor, "-") != 0)
            strcat(current.prefix, surround(current.fgColor, "%{F#", "}"));
        else
            strcat(current.prefix, surround(current.fgColor, "%{F", "}"));
        if (strcmp(current.bgColor, "-") != 0)
            strcat(current.prefix, surround(current.bgColor, "%{B#", "}"));
        else
            strcat(current.prefix, surround(current.fgColor, "%{B", "}"));
        // Set click & scroll events
        int clickableAreas = 0;
        if (strcmp(current.onLeftClick, "NULL") != 0) {
            strcat(current.prefix, surround(current.onLeftClick, "%{A1:", ":}"));
            clickableAreas++;
        }
        if (strcmp(current.onMiddleClick, "NULL") != 0) {
            strcat(current.prefix, surround(current.onMiddleClick, "%{A2:", ":}"));
            clickableAreas++;
        }
        if (strcmp(current.onRightClick, "NULL") != 0) {
            strcat(current.prefix, surround(current.onRightClick, "%{A3:", ":}"));
            clickableAreas++;
        }
        if (strcmp(current.onScrollUp, "NULL") != 0) {
            strcat(current.prefix, surround(current.onScrollUp, "%{A4:", ":}"));
            clickableAreas++;
        }
        if (strcmp(current.onScrollDown, "NULL") != 0) {
            strcat(current.prefix, surround(current.onScrollDown, "%{A5:", ":}"));
            clickableAreas++;
        }
        current.suffix = malloc(2048);
        strcpy(current.suffix, "");
        for (int i = 0; i < clickableAreas; i++) {
            strcat(current.suffix, "%{A}");
        }
        strcat(current.suffix, "%{F-}");
        strcat(current.suffix, "%{B-}");

        printf("PREFIX: %s\n", current.prefix);
        printf("SUFFIX: %s\n", current.suffix);

        blocks[l] = current;

        l++;
    }

    fclose(file);

    return blocks;
}

