//
// Created by kosenko on 9/6/24.
//

#include "tables.h"
#include <stdio.h>
#include <string.h>
#include "../library/terminal_bfo/colors_bfo/colors.h"

void print_table(char **header, char ***table, unsigned int columns, unsigned int rows, char *column_separator, char header_separator, char *side_separator){
    unsigned int col_width[columns];
    for(unsigned int *col_width_ptr = col_width; col_width_ptr<col_width+columns; col_width_ptr++, header++){
        *col_width_ptr = strlen(*header);
    }
    for(char ***table_ptr = table; table_ptr<table+rows; table_ptr++){
        char **row_ptr = *table_ptr;
        for(unsigned int *col_width_ptr = col_width; col_width_ptr<col_width+columns; col_width_ptr++, row_ptr++){
            unsigned int str_len = strlen(*row_ptr);
            if(str_len>*col_width_ptr){
                *col_width_ptr = str_len;
            }
        }
    }
    header -= columns;

    printf("%s", side_separator);
    for(unsigned int *col_width_ptr = col_width; col_width_ptr<col_width+columns; col_width_ptr++, header++){
        if(col_width_ptr>col_width){
            printf("%s", column_separator);
        }
        printf("%s", *header);
        for(unsigned int spaces = *col_width_ptr - strlen(*header); spaces>0; spaces--){
            putchar(' ');
        }
    }
    printf("%s\n", side_separator);
    header -= columns;

    for(unsigned int sep_spaces = strlen(side_separator) * 2 + strlen(column_separator) * (columns - 1); sep_spaces>0; sep_spaces--){
        putchar(header_separator);
    }
    for(unsigned int *col_width_ptr = col_width; col_width_ptr<col_width+columns; col_width_ptr++){
        for(unsigned int i = 0; i<*col_width_ptr; i++){
            putchar(header_separator);
        }
    }
    putchar('\n');

    for(char ***table_ptr=table; table_ptr<table+rows; table_ptr++){
        printf("%s", side_separator);
        char **row_ptr = *table_ptr;
        for(unsigned int *col_width_ptr = col_width; col_width_ptr<col_width+columns; col_width_ptr++, row_ptr++){
            if(col_width_ptr>col_width){
                printf("%s", column_separator);
            }
            printf("%s", *row_ptr);
            for(unsigned int spaces = *col_width_ptr - strlen(*row_ptr); spaces>0; spaces--){
                putchar(' ');
            }
        }
        printf("%s\n", side_separator);
    }
}

void print_table_colored_header(char **header, unsigned int columns, unsigned int side_spaces,
                                COLOR (*get_header_color)(unsigned int col), unsigned int *col_width,
                                char* to_be_continued_cell){
    //TODO implement
}

void print_table_colored_body(char ***table, unsigned int columns, unsigned int rows,
                              unsigned int side_spaces,
                              COLOR (*get_body_colors)(unsigned int row, unsigned int col, char selected),
                              unsigned int *col_width, unsigned int selected, char selection_present,
                              unsigned int max_rows, char* to_be_continued, COLOR to_be_continued_color,
                              char* to_be_continued_cell){
    //TODO implement
}

void print_table_colored(char **header, char ***table, unsigned int columns, unsigned int rows,
                         unsigned int side_spaces, COLOR (*get_header_color)(unsigned int col),
                         COLOR (*get_body_colors)(unsigned int row, unsigned int col, char selected),
                         unsigned int *col_width, unsigned int selected, char selection_present,
                         unsigned int max_rows, char* to_be_continued, COLOR to_be_continued_color,
                         char* to_be_continued_cell){
    /*if(header){
        print_table_colored_header(header, columns, side_spaces, get_header_color, col_width);
    }
    if(table){
        print_table_colored_body(table, columns, rows, side_spaces, get_body_colors, col_width, selected,
                                 selection_present, max_rows, to_be_continued, to_be_continued_color);
    }*/
}
