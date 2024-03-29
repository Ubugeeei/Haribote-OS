#include "boot.h"

struct Queue32 *keyqueue;
int keydata0;

void inthandler21(int *esp) {
    int data;
    io_out8(PIC0_OCW2, 0x61);
    data = io_in8(PORT_KEYDAT);
    queue32_put(keyqueue, data + keydata0);
    return;
}

#define PORT_KEYSTA 0x0064
#define KEYSTA_SEND_NOTREADY 0x02
#define KEYCMD_WRITE_MODE 0x60
#define KBC_MODE 0x47

void wait_KBC_sendready(void) {
    for (;;) {
        if ((io_in8(PORT_KEYSTA) & KEYSTA_SEND_NOTREADY) == 0) {
            break;
        }
    }
    return;
}

void init_keyboard(struct Queue32 *queue, int data0) {
    keyqueue = queue;
    keydata0 = data0;

    wait_KBC_sendready();
    io_out8(PORT_KEYCMD, KEYCMD_WRITE_MODE);
    wait_KBC_sendready();
    io_out8(PORT_KEYDAT, KBC_MODE);
    return;
}
