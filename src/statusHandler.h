#ifndef STATUS_HANDLER
#define STATUS_HANDLER

#include "structs.h"


char *surround(char *stringToSurround, char *surrounderOne, char *surrounderTwo);
char *setAttribute(char *content, const char **attributeConfig, char *attributeContent);
void writeFullStatus(block *blocks, int numOfBlocks);
int updateStatus(block *blockToUpdate);

#endif
