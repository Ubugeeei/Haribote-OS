#include "../apilib.h"

void HariMain(void) {
    int win, i, j, dis;
    char buf[216 * 237];
    struct POINT {
        int x, y;
    };
    static struct POINT table[16] = {
        {204, 129}, {195, 90},  {172, 58},  {137, 38}, {98, 34},  {61, 46},
        {31, 73},   {15, 110},  {15, 148},  {31, 185}, {61, 212}, {98, 224},
        {137, 220}, {172, 200}, {195, 168}, {204, 129}};

    win = open(buf, 216, 237, -1, "bball");
    box_fill_window(win, 8, 29, 207, 228, 0);
    for (i = 0; i <= 14; i++) {
        for (j = i + 1; j <= 15; j++) {
            dis = j - i;  // Distance between 2 points
            if (dis >= 8) {
                dis = 15 - dis;
            }  // Count in reverse order
            if (dis != 0) {
                // clang-format off
                draw_line_window(win, table[i].x, table[i].y, table[j].x, table[j].y, 8 - dis);
                // clang-format on
            }
        }
    }

    for (;;) {
        if (get_key(1) == 0x0a) {
            break;
        }  // Enter to break
    }
    api_end();
}
