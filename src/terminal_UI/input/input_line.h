//
// Created by kosenko on 9/23/24.
//

#ifndef BFO_CLI_READING_LIST_SRC_TERMINAL_UI_INPUT_INPUT_LINE_H
#define BFO_CLI_READING_LIST_SRC_TERMINAL_UI_INPUT_INPUT_LINE_H

#include "../../library/terminal_bfo/colors_bfo/colors.h"

typedef struct
{
    COLOR *main_color, *cursor_color;
    string text;
    unsigned int terminal_row, terminal_col_start, terminal_col_end, from_char, cursor;
    char stop;
} input_line;

void print_input_line(input_line *line);

void start_input_line_IO(input_line *line);

#endif //BFO_CLI_READING_LIST_SRC_TERMINAL_UI_INPUT_INPUT_LINE_H
