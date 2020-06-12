#ifndef MAIN
#define MAIN

typedef struct {
	char* icon;
	char* command;
	unsigned int signal;
} block;

void initPipe();
void closePipe();
void writeStatus(char *status);
const block *getBlock(int signal);
void parseConfig();
void initializeBlock(const block *);
void sighander(int signal);

#endif
