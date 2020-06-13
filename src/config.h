// Icon, Command, Interval, Signal (Except 2 & 9), Foreground Color, Background Color, Align
static const block blocks[] = {
	{"🍍",	"powermenu.sh", 0, 3, "#f8f8ff", "", 'l'},
	{"",	"bspwm.sh", 1, 4, "#f8f8ff", "", 'l'},
	{"",	"cmus.sh", 1,	5, "#f8f8ff", "", 'c'},
	{"🔈",	"volume.sh", 0,	6, "#f8f8ff", "", 'c'},
	{"",	"layout.sh", 0,	7, "#f8f8ff", "", 'r'},
	{"",	"network.sh", 60,	8, "#f8f8ff", "", 'r'},
	{"",	"date.sh", 60,	10, "#f8f8ff", "", 'r'},
};


static int MAX_LEN = 1500;
static char *DELIM = "   ";
static char *DELIM_ICON = " ";
