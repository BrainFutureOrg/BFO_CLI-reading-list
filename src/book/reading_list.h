//
// Created by maksym on 8/20/24.
//

#ifndef BFO_CLI_READING_LIST_SRC_BOOK_READING_LIST_H
#define BFO_CLI_READING_LIST_SRC_BOOK_READING_LIST_H

#include <stdlib.h>

typedef struct book{
    char* book_name;
    char* book_path;
} book;

typedef struct book_list{
    book this_book;
    struct book_list *next;
} book_list;

typedef struct themed_book_list{
    char* theme;
    book_list* this_book_list;
    struct themed_book_list *next;
} themed_book_list;

book book_create(char* book_name, char* book_path);
void free_book(book this_book);

book_list* book_list_add_book(book_list *this_book_list, book new_book);
book_list* book_list_delete_book(book_list *this_book_list, char* book_path);
void free_book_list(book_list *this_book_list);

themed_book_list* themed_book_list_add_book_list(themed_book_list *this_themed_book_list, char* theme, book_list* new_book_list);
themed_book_list* themed_book_list_add_book(themed_book_list *this_themed_book_list, char* theme, book new_book);
themed_book_list* themed_book_list_delete_book(themed_book_list *this_themed_book_list, char* theme, char* book_path);
themed_book_list* themed_book_list_delete_theme(themed_book_list *this_themed_book_list, char* theme);

void free_themed_book_list(themed_book_list *this_themed_book_list);

#endif //BFO_CLI_READING_LIST_SRC_BOOK_READING_LIST_H
