//
// Created by kosenko on 9/23/24.
//

#include "input_line.h"
#include "../../library/terminal_bfo/terminal_funcs.h"
#include "../../terminal_IO/read_keys.h"

void print_input_line(input_line *line)
{
    terminal_goto_xy(line->terminal_col_start, line->terminal_row);
    if (line->main_color)
    {
        printf("%s", line->main_color->line);
    }
    else
    {
        color_to_default();
    }
    unsigned int printed_chars = strlen(line->text.line) - line->from_char,
        width = line->terminal_col_end - line->terminal_col_start;
    if (printed_chars > width)
    {
        printed_chars = width;
    }
    unsigned int spaces = width - printed_chars;
    for (char *p = line->text.line + line->from_char; printed_chars > 0; printed_chars--, p++)
    {
        if (p - line->text.line == line->cursor && line->cursor_color)
        {
            printf("%s", line->cursor_color->line);
            putchar(*p);
            if (line->main_color)
            {
                printf("%s", line->main_color->line);
            }
            else
            {
                color_to_default();
            }
        }
        else
        {
            putchar(*p);
        }
    }
    for (; spaces > 0; spaces--)
    {
        putchar(' ');
    }
}

void func_char(char c, void *args)
{
    input_line *line = args;
    if (c == '\n')
    {
        line->stop = 1;
        return;
    }
    if (c == DEL)
    {
        if (line->cursor > 0)
        {
            if (line->cursor == line->from_char)
            {
                line->from_char--;
            }
            line->cursor--;
            delete_from_string_multiline(&line->text, 0, line->cursor);
        }
        return;
    }
    insert_into_string_multiline(&line->text, c, 0, line->cursor);
}

void func_arrow(arrow_key arrow, void *args)
{
    input_line *line = args;
    if (arrow == ARROW_KEY_LEFT)
    {
        if (line->cursor > 0)
        {
            if (line->cursor == line->from_char)
            {
                line->from_char--;
            }
            line->cursor--;
        }
    }
    else if (arrow == ARROW_KEY_RIGHT)
    {
        if (line->cursor < strlen(line->text.line))
        {
            if (line->cursor == line->from_char + line->terminal_col_end - line->terminal_col_start)
            {
                line->from_char++;
            }
            line->cursor++;
        }
    }
}

void start_input_line_IO(input_line *line)
{
    key_processing_callbacks callbacks;
    callbacks.args = line;
    callbacks.process_arrow = func_arrow;
    callbacks.process_char = func_char;
    callbacks.process_ctrl = NULL;
    while (!line->stop)
    {
        start_read_process_keys(callbacks);
    }
}