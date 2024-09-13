//
// Created by kosenko on 9/13/24.
//

#ifndef BFO_CLI_READING_LIST_SRC_TERMINAL_UI_LAYOUT_BASE_CONTAINERS_H
#define BFO_CLI_READING_LIST_SRC_TERMINAL_UI_LAYOUT_BASE_CONTAINERS_H

#include "../basic_structs.h"

typedef struct
{
    void *args;
    void
    (*print)(void *args);
    void
    (*resize)(void *args, row_col_rectangle bounds);
} printable_resizable;

#endif //BFO_CLI_READING_LIST_SRC_TERMINAL_UI_LAYOUT_BASE_CONTAINERS_H
