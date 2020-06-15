#ifndef SIG_HANDLER
#define SIG_HANDLER

#include "structs.h"

void addSignal(block *b);
int getIndex(int signal);
void parseSignals(block *blocks_, int *numberOfBlocks_, int whitelistPID);
void sighandler(int signal);

#endif
