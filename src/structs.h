#ifndef STRUCTS
#define STRUCTS

typedef struct {
    unsigned int interval;
    unsigned int signal;
    char *icon;
    char *command;
    char *alignment;
    char *status;
    char *bgColor;
    char *fgColor;
    char *prefix;
    char *suffix;
    char *onLeftClick;
    char *onMiddleClick;
    char *onRightClick;
    char *onScrollUp;
    char *onScrollDown;
} block;

#endif
