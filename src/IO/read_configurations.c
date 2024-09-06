//
// Created by maksym on 8/20/24.
//

#include "read_configurations.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "reading_list.h"

#define MAX_LINE_LENGTH 512

// Function to read themed book list from a text configuration file
themed_book_list* read_txt_config(char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    themed_book_list *head = NULL;
    themed_book_list *current_theme = NULL;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        char *trimmed_line = strtok(line, "\n");

        // Process theme line
        if (strncmp(trimmed_line, "theme - ", 8) == 0) {
            char *theme = strtok(trimmed_line + 8, ":");
            write_log(DEBUG, "theme = %s, line = %s", theme, trimmed_line);
            current_theme = themed_book_list_add_book_list(head, theme, NULL);
            if (head == NULL) {
                head = current_theme;
            }
        }
            // Process name and path lines
        else if (strncmp(trimmed_line, "name - ", 7) == 0) {
            int end_of_name = 6;
            while (strncmp(trimmed_line + (++end_of_name), "; path - ", 9) != 0);
            char *book_name = calloc(end_of_name - 6, sizeof(char ));
            strncpy(book_name, trimmed_line + 7, end_of_name - 7);
            book_name[end_of_name - 7] = '\0';
            fgets(line, sizeof(line), file);
            char *book_path = trimmed_line + end_of_name + 9;
            write_log(DEBUG, "book name - %s, book path - %s", book_name, book_path);

            // If book_name is empty, use the file name from the path
            if (strcmp(book_name, "") == 0) {
                book_name = strrchr(book_path, '/');
                if (book_name != NULL) {
                    book_name++;  // Skip '/'
                } else {
                    book_name = book_path;
                }
            }

            book new_book = book_create(book_name, book_path);
            current_theme->this_book_list = book_list_add_book(current_theme->this_book_list, new_book);
            free(book_name);
        }
    }

    fclose(file);
    return head;
}

// Function to write themed book list to a text configuration file
void write_txt_config(char *path, themed_book_list *list) {
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    themed_book_list *current_theme = list;
    while (current_theme != NULL) {
        fprintf(file, "theme - %s:\n", current_theme->theme);

        book_list *current_book_list = current_theme->this_book_list;
        while (current_book_list != NULL) {
            fprintf(file, "name - %s; path - %s\n", current_book_list->this_book.book_name, current_book_list->this_book.book_path);
            current_book_list = current_book_list->next;
        }

        current_theme = current_theme->next;
    }

    fclose(file);
}

read_conf create_read_conf_txt(){
    read_conf result;
    result.read_config = read_txt_config;
    result.write_config = write_txt_config;
    return result;
}