#include "apilib.h"

char buf[150 * 50];

void HariMain(void) {
	int win;
	win = open(buf, 150, 50, -1, "hello");
	box_fill_window(win, 8, 36, 141, 43, 3);
	putstr_window(win, 28, 28, 0, 12, "hello, world");
	api_end();
}
