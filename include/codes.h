#pragma once

#define ENABLE_ALT_BUFFER "\x1b[?1049h"
#define DISABLE_ALT_BUFFER "\x1b[?1049l"
#define HIDE_CURSOR "\x1b[?25l"
#define SHOW_CURSOR "\x1b[?25h"
#define START_NEXT_LINE "\x1b[1E"
#define ERASE_SCREEN "\x1b[2J"
#define DISABLE_LINE_WRAP "\x1b[7l"
#define ENABLE_LINE_WRAP "\x1b[7h"