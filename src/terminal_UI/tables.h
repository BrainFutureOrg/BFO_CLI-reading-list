//
// Created by kosenko on 9/6/24.
//

#ifndef BFO_CLI_READING_LIST_SRC_TERMINAL_UI_TABLES_H
#define BFO_CLI_READING_LIST_SRC_TERMINAL_UI_TABLES_H

#include "../terminal_bfo/colors_bfo/colors.h"

void print_table(char **header,
                 char ***table,
                 unsigned int columns,
                 unsigned int rows,
                 char *column_separator,
                 char header_separator,
                 char *side_separator);

typedef struct
{
    unsigned int side_spaces;
    COLOR
    (*get_header_color)(unsigned int col);
    COLOR
    (*get_body_color)(unsigned int row, unsigned int col, char selected);
    char *to_be_continued;
    COLOR to_be_continued_color;
    char *to_be_continued_cell;
    char fill_remainder_rows;
    COLOR remainder_rows_color;
} table_colored_settings;

typedef struct
{
    char **header;
    char ***table;
    unsigned int columns;
    unsigned int rows;
    unsigned int *col_width;
    unsigned int selected;
    char selection_present;
    unsigned int max_rows;
    table_colored_settings *settings;
    unsigned int terminal_row_start;
    unsigned int terminal_col_start;
    unsigned int from_row;
} table_colored;

void print_table_colored(table_colored table);

#endif //BFO_CLI_READING_LIST_SRC_TERMINAL_UI_TABLES_H

