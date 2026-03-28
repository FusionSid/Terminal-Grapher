#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "codes.h"
#include "screen.h"

static struct termios orig_termios;

void init() {
    setbuf(stdout, NULL);
    update_window_size();
    printf(ENABLE_ALT_BUFFER ERASE_SCREEN HIDE_CURSOR DISABLE_LINE_WRAP);
}

void deinit() {
    printf(ERASE_SCREEN DISABLE_ALT_BUFFER ENABLE_LINE_WRAP SHOW_CURSOR);
}

void disable_raw_mode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); }

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);

    struct termios raw = orig_termios;

    raw.c_lflag &= ~(ECHO | ICANON);  // turn off echo and canonical
    raw.c_cc[VMIN] = 0;               // min bytes to read
    raw.c_cc[VTIME] = 1;              // timeout in 1/10 of a sec

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
