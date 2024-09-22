//
// Created by kosenko on 9/8/24.
//

#ifndef BFO_CLI_READING_LIST_SRC_TERMINAL_UI_MENUS_CHAR_MENU_H
#define BFO_CLI_READING_LIST_SRC_TERMINAL_UI_MENUS_CHAR_MENU_H

#include "../tables.h"
#include "../basic_structs.h"

typedef struct
{
    char to_match;
    char *description;
    void
    (*func)(void *args);
    void *args;
} char_menu_callback;

typedef struct
{
    void
    (*func)(void *args);
    void *args;
} char_menu_default_callback;

typedef enum
{
    CHAR_MENU_ORIENTATION_HORIZONTAL,
    CHAR_MENU_ORIENTATION_VERTICAL
} char_menu_orientation;

typedef struct
{
    table_colored_settings *table_settings;
    char **header; // expects NULL or 2 char*
    char key_first; // 1 if table is key - description, 0 if description - key
    char_menu_callback *callbacks;
    unsigned int callback_num;
    char_menu_orientation orientation;
    row_col_rectangle bounds;
    char_menu_default_callback default_callback;
    char stop;
} char_menu;

void print_char_menu(char_menu *menu);

void start_char_menu_IO(char_menu *menu);

#endif //BFO_CLI_READING_LIST_SRC_TERMINAL_UI_MENUS_CHAR_MENU_H
