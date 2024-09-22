//
// Created by kosenko on 9/8/24.
//

#include "table_selection_menu.h"

void print_table_selection_menu(table_selection_menu *menu)
{
    print_table_colored(*menu->table);
}

void func_char(char c, void *args)
{
    table_selection_menu *menu = args;
    if (menu->callback.func_char)
    {
        menu->callback.func_char(menu->table->selected, c, args);
    }
}

void func_ctrl(char c, void *args)
{
    table_selection_menu *menu = args;
    if (menu->callback.func_ctrl)
    {
        menu->callback.func_ctrl(menu->table->selected, c, args);
    }
}

void func_arrow(arrow_key arrow, void *args)
{
    table_selection_menu *menu = args;
    if (arrow == ARROW_KEY_UP && menu->table->selected > 0)
    {
        menu->table->selected--;
        if (menu->table->selected < menu->table->from_row)
        {
            menu->table->from_row--;
        }
        print_table_selection_menu(menu);
    }
    else if (arrow == ARROW_KEY_DOWN && menu->table->selected < menu->table->rows - 1)
    {
        menu->table->selected++;
        unsigned int last_printed = menu->table->from_row + menu->table->max_rows - (menu->table->from_row > 0);
        if (menu->table->rows - menu->table->from_row + (menu->table->from_row > 0) > menu->table->max_rows)
        {
            last_printed--;
        }
        if (menu->table->selected > last_printed)
        {
            menu->table->from_row++;
        }
        print_table_selection_menu(menu);
    }
    if (menu->callback.func_arrow)
    {
        menu->callback.func_arrow(menu->table->selected, arrow, args);
    }
}

void start_table_selection_menu_IO(table_selection_menu *menu)
{
    key_processing_callbacks callbacks;
    callbacks.process_ctrl = func_ctrl;
    callbacks.process_char = func_char;
    callbacks.process_arrow = func_arrow;
    callbacks.args = menu;
    while (!menu->stop)
    {
        start_read_process_keys(callbacks);
    }
}