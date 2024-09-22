//
// Created by kosenko on 9/8/24.
//

#include "char_menu.h"
#include "../../terminal_IO/read_keys.h"

void match_char_callback(char c, void *menu_ptr)// TODO finish
{
    char_menu *menu = menu_ptr;
    char_menu_callback *callback_ptr = menu->callbacks;
    for (int i = 0; i < menu->callback_num; i++, callback_ptr++)
    {
        if (callback_ptr->to_match == c)
        {
            callback_ptr->func(callback_ptr->args);
            break;
        }
    }
}

void start_char_menu_IO(char_menu *menu)// TODO implement terminal mode switching
{
    key_processing_callbacks callbacks;
    callbacks.args = menu;
    callbacks.process_char = match_char_callback;
    callbacks.process_arrow = NULL;
    callbacks.process_ctrl = NULL;
    while (!menu->stop)
    {
        start_read_process_keys(callbacks);
    }
}

void print_char_menu(char_menu *menu)
{
    table_colored table;
    table.settings = menu->table_settings;
    table.selection_present = 0;
    table.terminal_row_start = menu->bounds.row_start;
    table.terminal_col_start = menu->bounds.col_start;
    table.from_row = 0;
    table.header = menu->header;
    table.max_rows = menu->bounds.row_end - menu->bounds.row_start - (table.header != NULL);
    char key_last = (char)!menu->key_first;
    if (menu->orientation == CHAR_MENU_ORIENTATION_HORIZONTAL)//TODO fix same as next
    {
        char *body[1][2 * menu->callback_num];
        unsigned int col_width[2 * menu->callback_num];
        for (int i = 0; i < menu->callback_num; i++)
        {
            char c[2] = {menu->callbacks[i].to_match, '\0'};
            body[0][2 * i + key_last] = c;
            col_width[2 * i + key_last] = menu->table_settings->side_spaces + 1;
            body[0][2 * i + menu->key_first] = menu->callbacks[i].description;
            col_width[2 * i + menu->key_first] =
                menu->table_settings->side_spaces + strlen(menu->callbacks[i].description);
            if (menu->header)
            {
                for (int j = 0; j < menu->callback_num * 2; j++)
                {
                    unsigned int header_len = strlen(menu->header[j]) + menu->table_settings->side_spaces;
                    if (col_width[j] < header_len)
                    {
                        col_width[j] = header_len;
                    }
                }
            }
        }
        table.table = (char ***)body;
        table.rows = 1;
        table.columns = 2 * menu->callback_num;
        table.col_width = col_width;
        print_table_colored(table);
    }
    else if (menu->orientation == CHAR_MENU_ORIENTATION_VERTICAL)
    {
        char **body[menu->callback_num];
        unsigned int desc_width = 0;
        for (int i = 0; i < menu->callback_num; i++)
        {
            body[i] = malloc(2 * sizeof(char *));
            char *c = malloc(2 * sizeof(char));
            c[0] = menu->callbacks[i].to_match;
            c[1] = '\0';
            body[i][key_last] = c;
            body[i][menu->key_first] = menu->callbacks[i].description;
            unsigned int description_len = strlen(menu->callbacks[i].description);
            if (description_len > desc_width)
            {
                desc_width = description_len;
            }
        }
        desc_width += menu->table_settings->side_spaces;
        unsigned int col_width[2];
        col_width[key_last] = 1 + menu->table_settings->side_spaces;
        col_width[menu->key_first] = desc_width;
        if (menu->header)
        {
            for (int i = 0; i < 2; i++)
            {
                unsigned int header_len = strlen(menu->header[i]) + menu->table_settings->side_spaces;
                if (col_width[i] < header_len)
                {
                    col_width[i] = header_len;
                }
            }
        }
        table.table = body;
        table.rows = menu->callback_num;
        table.columns = 2;
        table.col_width = col_width;
        print_table_colored(table);
    }
}