// Icon, Command, Interval, Signal (Except 2 & 9), Foreground Color, Background Color, Align
static const block blocks[] = {
	{" 🍍",	"powermenu.sh", 0, 3, "#f8f8ff", "", 'l'},
	{"",	"bspwm.sh", 1, 4, "#f8f8ff", "", 'l'},
	{"",	"cmus.sh", 1,	5, "#f8f8ff", "", 'l'},
	{" 🔈",	"volume.sh", 0,	6, "#f8f8ff", "#aa1d1f21", 'r'},
	{" 📁",	"free-space.sh", 0,	6, "#f8f8ff", "#aa1d1f21", 'r'},
	{" 🐒",	"layout.sh", 0,	7, "#f8f8ff", "#aa1d1f21", 'r'},
	{"",	"network.sh", 60,	8, "#f8f8ff", "#aa1d1f21", 'r'},
	{" ⏰",	"date.sh", 60,	10, "#f8f8ff", "#aa1d1f21", 'r'},
};


static int MAX_LEN = 1500;
static char *DELIM = "   ";
static char *DELIM_ICON = "";
