// Icon, Command, Interval, Signal (Except 2 & 9), Foreground Color, Background Color, Align
static const block blocks[] = {
	{"🍍",	"./test-scripts/powermenu.sh", 0, 3, "#f8f8ff", "", 'l'},
	{"",	"./test-scripts/bspwm.sh", 0, 4, "#171517", "#f8f8ff", 'l'},
	{"",	"./test-scripts/cmus.sh", 0,	5, "#f8f8ff", "", 'c'},
	{"",	"./test-scripts/volume.sh", 0,	6, "#f8f8ff", "", 'c'},
	{"",	"./test-scripts/layout.sh", 0,	7, "#f8f8ff", "", 'r'},
	{"",	"./test-scripts/network.sh", 60,	8, "#f8f8ff", "", 'r'},
	{"",	"./test-scripts/date.sh", 5,	10, "#f8f8ff", "", 'r'},
};


static int MAX_LEN = 200;
static char *DELIM = "  |  ";
static char *DELIM_ICON = "  ";
