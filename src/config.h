// Icon, Command, Interval (Seconds), Signal (> 2)
static const block blocks[] = {
	{"🐨",	"./test-scripts/date.sh",	3},
	{"🦏",	"./test-scripts/free-space.sh",	4},
	/* {"🦜",	"date",	5}, */
	/* {"🐶",	"date",	6}, */
	/* {"🦈",	"date",	7}, */
};


static int MAX_LEN = 200;
static char *DELIM = "   |   ";
static char *DELIM_ICON = "  ";
