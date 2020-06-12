// Icon, Command, Interval, Signal (> 2), Foreground Color, Background Color
static const block blocks[] = {
	{"🐨",	"./test-scripts/date.sh", 5, 3, "#f8f8ff", "#32cd32"},
	{"🦏",	"./test-scripts/free-space.sh", 0, 4, "#f8f8ff", "#8040bf"},
	/* {"🦜",	"date",	5}, */
	/* {"🐶",	"date",	6}, */
	/* {"🦈",	"date",	7}, */
};


static int MAX_LEN = 200;
static char *DELIM = "   |   ";
static char *DELIM_ICON = "  ";
