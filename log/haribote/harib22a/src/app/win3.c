int open(char *buf, int xsiz, int ysiz, int col_inv, char *title);
void putstr_window(int win, int x, int y, int col, int len, char *str);
void box_fill_window(int win, int x0, int y0, int x1, int y1, int col);
void init_malloc(void);
char *malloc(int size);
void api_end(void);

void HariMain(void) {
    char *buf;
    int win;

    init_malloc();
    buf = malloc(150 * 50);
    win = open(buf, 150, 50, -1, "hello");
    box_fill_window(win, 8, 36, 141, 43, 6);
    putstr_window(win, 28, 28, 0, 12, "hello, world");
    api_end();
}
