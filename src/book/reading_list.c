//
// Created by maksym on 8/20/24.
//

#include "reading_list.h"
#include <string.h>

book book_create(char* book_name, char* book_path)
{
    return  (book){book_name, book_path};
}

void free_book(book this_book)
{
    free(this_book.book_name);
    free(this_book.book_path);
}

book_list* book_list_add_book(book_list *this_book_list, book new_book)
{
    book_list *new_element = calloc(sizeof(book_list), 1);
    new_element->next = this_book_list;
    new_element->this_book = new_book;
    return new_element;
}

#define free_book_list_part_with_action(action, list_name) book_list *for_free = list_name; \
                                                action                                \
                                                free_book(for_free->this_book);       \
                                                free(for_free);

void free_book_list(book_list *this_book_list)
{
    while(this_book_list != NULL)
    {
        free_book_list_part_with_action(this_book_list = this_book_list->next;, this_book_list)
    }
}

themed_book_list* themed_book_list_add_book_list(themed_book_list *this_themed_book_list, char* theme, book_list* new_book_list)
{
    themed_book_list *new_element = calloc(sizeof(themed_book_list), 1);
    new_element->next = this_themed_book_list;
    new_element->theme = theme;
    new_element->this_book_list = new_book_list;
    return new_element;
}

#define next_book_from_list this_book_list->next->this_book
book_list* book_list_delete_book(book_list *this_book_list, char* book_path)
{
    if(strcmp(this_book_list->this_book.book_path, book_path) == 0)
    {
        free_book_list_part_with_action(this_book_list = this_book_list->next;, this_book_list)
        return this_book_list;
    }

    book_list *list_head = this_book_list;
    while(strcmp(next_book_from_list.book_path, book_path) != 0)
    {
        this_book_list = this_book_list->next;
        if(this_book_list->next == NULL)
        {
            return list_head;
        }

    }
    free_book_list_part_with_action(this_book_list->next = this_book_list->next->next;, this_book_list->next)
    return list_head;
}


themed_book_list* themed_book_list_add_book(themed_book_list *this_themed_book_list, char* theme, book new_book)
{
    themed_book_list *list_head = this_themed_book_list;
    while(strcmp(this_themed_book_list->theme, theme) != 0)
    {
        if(this_themed_book_list->next == NULL)
        {
            book_list *new_list = book_list_add_book(NULL, new_book);
            this_themed_book_list = themed_book_list_add_book_list(this_themed_book_list, theme, new_list);
            return this_themed_book_list;
        }
        this_themed_book_list = this_themed_book_list->next;
    }
    this_themed_book_list->this_book_list = book_list_add_book(this_themed_book_list->this_book_list, new_book);
    return list_head;
}

#define free_themed_book_list_part_with_action(action, list_name) themed_book_list *for_free = list_name;  \
                                                       action                                               \
                                                       free_book_list(for_free->this_book_list);            \
                                                       free(for_free->theme);                               \
                                                       free(for_free);

#define delete_book_with_spec_theme(action, list_name)  book_list *new_list = book_list_delete_book(list_name->this_book_list, book_path); \
                                                        if(new_list == NULL)                                                               \
                                                        {                                                                                  \
                                                            free_themed_book_list_part_with_action(action, list_name)                                 \
                                                        }                                                                                  \
                                                        else {                                                                             \
                                                            list_name->this_book_list = new_list;                                          \
                                                        }                                                                                  \

themed_book_list* themed_book_list_delete_book(themed_book_list *this_themed_book_list, char* theme, char* book_path)
{
    if(strcmp(this_themed_book_list->theme, theme) == 0)
    {
        delete_book_with_spec_theme(this_themed_book_list = this_themed_book_list->next;, this_themed_book_list)
        return this_themed_book_list;
    }

    themed_book_list *list_head = this_themed_book_list;
    while(strcmp(this_themed_book_list->next->theme, theme) != 0)
    {
        this_themed_book_list = this_themed_book_list->next;
        if(this_themed_book_list->next == NULL)
        {
            return list_head;
        }

    }
    delete_book_with_spec_theme(this_themed_book_list->next = this_themed_book_list->next->next;, this_themed_book_list->next)
    return list_head;
}

themed_book_list* themed_book_list_delete_theme(themed_book_list *this_themed_book_list, char* theme)
{
    if(strcmp(this_themed_book_list->theme, theme) == 0)
    {
        free_themed_book_list_part_with_action(this_themed_book_list = this_themed_book_list->next;, this_themed_book_list)
        return this_themed_book_list;
    }

    themed_book_list *list_head = this_themed_book_list;
    while(strcmp(this_themed_book_list->next->theme, theme) != 0)
    {
        this_themed_book_list = this_themed_book_list->next;
        if(this_themed_book_list->next == NULL)
        {
            return list_head;
        }

    }
    free_themed_book_list_part_with_action(this_themed_book_list->next = this_themed_book_list->next->next;, this_themed_book_list->next)
    return list_head;
}


void free_themed_book_list(themed_book_list *this_themed_book_list)
{
    while(this_themed_book_list != NULL)
    {
        free_themed_book_list_part_with_action(this_themed_book_list = this_themed_book_list->next;, this_themed_book_list)
    }
}