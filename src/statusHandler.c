#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Headers */
#include "main.h"

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
char *setAttribute(char *content, char **attributeConfig, char *attributeContent)
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
