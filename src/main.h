#ifndef MAIN
#define MAIN

typedef struct {
	char* icon;
	char* command;
	unsigned int interval;
	unsigned int signal;
	char* fgColor;
	char* bgColor;
} block;

void initPipe();
void closePipe();
void writeStatus(char *status);
void executeCommand(const block *current, char *status);
void *mainLoop();
const block *getBlock(int signal);
int getBlockIndex(int signal);
void parseConfig();
void parseSigs();
void initializeBlock(const block *current, int index);
void setBlockStatus(const block *current, int index);
char *getStatus();
void setStatus();
void sighandler(int signal);

#endif
