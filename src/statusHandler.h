#ifndef STATUS_HANDLER
#define STATUS_HANDLER

/* Configuration */
char *FOREGROUND_COLOR[3] = { "%{F", "}", "%{F-}" };
char *BACKGROUND_COLOR[3] = { "%{B", "}", "%{B-}" };
char *LINE_COLOR[3] = { "%{U", "}", "%{U-}" };
char *LEFT_CLICK[3] = { "%{A1:", ":}", "%{A1}" };
char *MIDDLE_CLICK[3] = { "%{A2:", ":}", "%{A2}" };
char *RIGHT_CLICK[3] = { "%{A3:", ":}", "%{A3}" };
char *SCROLL_UP_CLICK[3] = { "%{A4:", ":}", "%{A4}" };
char *SCROLL_DOWN_CLICK[3] = { "%{A5:", ":}", "%{A5}" };


char *surround(char *stringToSurround, char *surrounderOne, char *surrounderTwo);
char *setAttribute(char *content, char **attributeConfig, char *attributeContent);

#endif
