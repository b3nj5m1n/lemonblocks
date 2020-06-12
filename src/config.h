// Icon, Command, Interval, Signal (> 2), Foreground Color, Background Color
static const block blocks[] = {
	{"🐨",	"./test-scripts/date.sh", 5, 3, "#f8f8ff", "#32cd32"},
	{"🦏",	"./test-scripts/free-space.sh", 0, 4, "#f8f8ff", "#8040bf"},
	{"🦜",	"./test-scripts/volume.sh", 0,	5, "#f8f8ff", "#0077ea"},
	{"🐶",	"./test-scripts/layout.sh", 0,	6, "#f8f8ff", "#ff4d4d"},
	{"🦈",	"./test-scripts/network.sh", 60,	7, "#f8f8ff", "#2f2f2f"},
};


static int MAX_LEN = 200;
static char *DELIM = "   |   ";
static char *DELIM_ICON = "  ";
