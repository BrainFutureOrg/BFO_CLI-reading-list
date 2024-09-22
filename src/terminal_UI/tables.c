//
// Created by kosenko on 9/6/24.
//

#include "tables.h"
#include <stdio.h>
#include <string.h>
#include "../library/terminal_bfo/colors_bfo/colors.h"
#include "../library/terminal_bfo/terminal_funcs.h"

void print_table(char **header,
                 char ***table,
                 unsigned int columns,
                 unsigned int rows,
                 char *column_separator,
                 char header_separator,
                 char *side_separator)
{
    unsigned int col_width[columns];
    for (unsigned int *col_width_ptr = col_width; col_width_ptr < col_width + columns; col_width_ptr++, header++)
    {
        *col_width_ptr = strlen(*header);
    }
    for (char ***table_ptr = table; table_ptr < table + rows; table_ptr++)
    {
        char **row_ptr = *table_ptr;
        for (unsigned int *col_width_ptr = col_width; col_width_ptr < col_width + columns; col_width_ptr++, row_ptr++)
        {
            unsigned int str_len = strlen(*row_ptr);
            if (str_len > *col_width_ptr)
            {
                *col_width_ptr = str_len;
            }
        }
    }
    header -= columns;

    printf("%s", side_separator);
    for (unsigned int *col_width_ptr = col_width; col_width_ptr < col_width + columns; col_width_ptr++, header++)
    {
        if (col_width_ptr > col_width)
        {
            printf("%s", column_separator);
        }
        printf("%s", *header);
        for (unsigned int spaces = *col_width_ptr - strlen(*header); spaces > 0; spaces--)
        {
            putchar(' ');
        }
    }
    printf("%s\n", side_separator);

    for (unsigned int sep_spaces = strlen(side_separator) * 2 + strlen(column_separator) * (columns - 1);
         sep_spaces > 0; sep_spaces--)
    {
        putchar(header_separator);
    }
    for (unsigned int *col_width_ptr = col_width; col_width_ptr < col_width + columns; col_width_ptr++)
    {
        for (unsigned int i = 0; i < *col_width_ptr; i++)
        {
            putchar(header_separator);
        }
    }
    putchar('\n');

    for (char ***table_ptr = table; table_ptr < table + rows; table_ptr++)
    {
        printf("%s", side_separator);
        char **row_ptr = *table_ptr;
        for (unsigned int *col_width_ptr = col_width; col_width_ptr < col_width + columns; col_width_ptr++, row_ptr++)
        {
            if (col_width_ptr > col_width)
            {
                printf("%s", column_separator);
            }
            printf("%s", *row_ptr);
            for (unsigned int spaces = *col_width_ptr - strlen(*row_ptr); spaces > 0; spaces--)
            {
                putchar(' ');
            }
        }
        printf("%s\n", side_separator);
    }
}

void print_table_colored_header(table_colored table)
{
    unsigned int spaces_pre = table.settings->side_spaces / 2, spaces_post = table.settings->side_spaces - spaces_pre,
        to_be_continued_len =
        strlen(table.settings->to_be_continued_cell);
    unsigned int *width_ptr = table.col_width;
    terminal_goto_xy(table.terminal_col_start, table.terminal_row_start);
    for (unsigned int c = 0; c < table.columns; c++, table.col_width++, table.header++, width_ptr++)
    {
        COLOR color = table.settings->get_header_color(c);
        printf("%s", color.line);
        free_color(color);
        for (int i = 0; i < spaces_pre; i++)
        {
            putchar(' ');
        }
        unsigned int str_chars = strlen(*table.header);
        char bigger = 0;
        if (str_chars > *width_ptr - table.settings->side_spaces)
        {
            str_chars = *width_ptr - table.settings->side_spaces - to_be_continued_len;
            bigger = 1;
        }
        char *str_ptr = *table.header;
        for (int i = 0; i < str_chars; i++, str_ptr++)
        {
            putchar(*str_ptr);
        }
        if (bigger)
        {
            printf("%s", table.settings->to_be_continued_cell);
        }
        for (int i = 0; i < /*spaces_post*/ *width_ptr - spaces_pre - str_chars; i++)
        {
            putchar(' ');
        }
    }
    color_to_default();
}

void print_to_be_continued_row(unsigned int terminal_row,
                               unsigned int terminal_col,
                               unsigned int row_width,
                               COLOR color,
                               char *line)
{
    unsigned int continued_len = strlen(line), continued_spaces_pre = (row_width - continued_len) / 2,
        continued_spaces_post = row_width - continued_len - continued_spaces_pre;
    terminal_goto_xy(terminal_col, terminal_row);
    printf("%s", color.line);
    for (int i = 0; i < continued_spaces_pre; i++)
    {
        putchar(' ');
    }
    printf("%s", line);
    for (int i = 0; i < continued_spaces_post; i++)
    {
        putchar(' ');
    }
    color_to_default();
}

void print_table_colored_body(table_colored table)
{
    unsigned int spaces_pre = table.settings->side_spaces / 2, spaces_post = table.settings->side_spaces - spaces_pre,
        to_be_continued_len =
        strlen(table.settings->to_be_continued_cell);
    unsigned int terminal_row = table.terminal_row_start + (table.header != NULL);
    unsigned int printed_rows = table.rows - table.from_row;
    char not_first = table.from_row > 0, to_be_continued = 0;
    if (printed_rows + not_first > table.max_rows)
    {
        printed_rows -= 1 + not_first;
        to_be_continued = 1;
    }
    unsigned int col_len_sum = 0;
    for (unsigned int *len_ptr = table.col_width; len_ptr < table.col_width + table.columns; len_ptr++)
    {
        col_len_sum += *len_ptr;
    }

    if (not_first)
    {
        print_to_be_continued_row(terminal_row,
                                  table.terminal_col_start,
                                  col_len_sum,
                                  table.settings->to_be_continued_color,
                                  table.settings->to_be_continued);
        terminal_row++;
    }
    table.table += table.from_row;
    for (unsigned int i = 0; i < printed_rows; i++, terminal_row++, table.table++)
    {
        terminal_goto_xy(table.terminal_col_start, terminal_row);
        char **row_ptr = *table.table;
        unsigned int *width_ptr = table.col_width;
        for (unsigned int j = 0; j < table.columns; j++, row_ptr++, width_ptr++)
        {
            COLOR color = table.settings->get_body_color(i, j, table.selection_present && i == table.selected);
            printf("%s", color.line);
            free_color(color);
            for (int k = 0; k < spaces_pre; k++)
            {
                putchar(' ');
            }
            unsigned int str_chars = strlen(*row_ptr);
            char bigger = 0;
            if (str_chars > *width_ptr - table.settings->side_spaces)
            {
                str_chars = *table.col_width - table.settings->side_spaces - to_be_continued_len;
                bigger = 1;
            }
            char *str_ptr = *row_ptr;
            for (int k = 0; k < str_chars; k++, str_ptr++)
            {
                putchar(*str_ptr);
            }
            if (bigger)
            {
                printf("%s", table.settings->to_be_continued_cell);
            }
            for (int k = 0; k < *width_ptr - spaces_pre - str_chars; k++)
            {
                putchar(' ');
            }
        }
        color_to_default();
    }
    if (to_be_continued)
    {
        print_to_be_continued_row(terminal_row,
                                  table.terminal_col_start,
                                  col_len_sum,
                                  table.settings->to_be_continued_color,
                                  table.settings->to_be_continued);
    }
    else if (table.settings->fill_remainder_rows)
    {
        for (unsigned int remainder_rows = table.max_rows - printed_rows - not_first; remainder_rows > 0;
             remainder_rows--, terminal_row++)
        {
            terminal_goto_xy(table.terminal_col_start, terminal_row);
            printf("%s", table.settings->to_be_continued_color.line);
            for (int i = 0; i < col_len_sum; i++)
            {
                putchar(' ');
            }
            color_to_default();
        }
    }
}

void print_table_colored(table_colored table)
{
    if (table.header)
    {
        print_table_colored_header(table);
    }
    if (table.table)
    {
        print_table_colored_body(table);
    }
}
