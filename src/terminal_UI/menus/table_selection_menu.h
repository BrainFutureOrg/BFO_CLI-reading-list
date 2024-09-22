//
// Created by kosenko on 9/8/24.
//

#ifndef BFO_CLI_READING_LIST_SRC_TERMINAL_UI_MENUS_TABLE_SELECTION_MENU_H
#define BFO_CLI_READING_LIST_SRC_TERMINAL_UI_MENUS_TABLE_SELECTION_MENU_H

#include "../tables.h"
#include "../../terminal_IO/read_keys.h"

typedef struct
{
    void
    (*func_char)(unsigned int selected_row, char c, void *args);
    void
    (*func_arrow)(unsigned int selected_row, arrow_key arrow, void *args);
    void
    (*func_ctrl)(unsigned int selected_row, char c, void *args);
    void *args;
} table_selection_menu_callback;

typedef struct
{
    table_colored *table;
    table_selection_menu_callback callback;
    char stop;
} table_selection_menu;

void print_table_selection_menu(table_selection_menu *menu);

void start_table_selection_menu_IO(table_selection_menu *menu);

#endif //BFO_CLI_READING_LIST_SRC_TERMINAL_UI_MENUS_TABLE_SELECTION_MENU_H
