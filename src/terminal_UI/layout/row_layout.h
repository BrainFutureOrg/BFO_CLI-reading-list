//
// Created by kosenko on 9/13/24.
//

#ifndef BFO_CLI_READING_LIST_SRC_LAYOUT_ROW_LAYOUT_H
#define BFO_CLI_READING_LIST_SRC_LAYOUT_ROW_LAYOUT_H

#include "../basic_structs.h"
#include "base_containers.h"

typedef struct
{
    char visible;
    unsigned int min_rows, max_rows, min_cols;
    double desired_proportion;
    unsigned int
        collapse_order; //rows with higher collapse order collapse later than those with less. Works only on collapse from too few rows
    printable_resizable to_print;
} resizable_row;

typedef struct
{
    row_col_rectangle bounds;
    resizable_row *rows;
    unsigned int row_num;
} row_layout;

void print_row_layout(row_layout layout);

void resize_row_layout(row_layout *layout, row_col_rectangle bounds);

#endif //BFO_CLI_READING_LIST_SRC_LAYOUT_ROW_LAYOUT_H
