#include "start_menu.h"
#include <stdio.h>
#include <string.h>
#include "../IO/input.h"
#include "errno.h"
#include "../terminal_UI/tables.h"
#include "../book/book_opener.h"


#define DEFAULT_TABLE_SEPARATORS "|", '-', ""

void print_theme_list(themed_book_list *list, char add_id){
    if(!list){
        printf("List not specified ...\n");
        return;
    }
    char ** header = malloc((1 + add_id) * sizeof(char*));
    if(add_id){
        header[0] = "id";
        header[1] = "theme";
    }else{
        header[0] = "theme";
    }
    unsigned int rows = 0;
    for(themed_book_list *list_ptr = list; list_ptr!=NULL; list_ptr = list_ptr->next, rows++);
    // Yes, after this 100% un-optimal pass through whole list code is hyper-optimized. Reason is because I can.
    char ***table = malloc(rows * sizeof(char**)), ***table_ptr = table;
    unsigned int id=0, id_digit_change=10;
    unsigned char id_str_len=2; // first digit and '\0'
    for(themed_book_list *list_ptr = list; list_ptr!=NULL; list_ptr = list_ptr->next, table_ptr++, id++){
        *table_ptr = malloc((1 + add_id) * sizeof(char*));
        if(add_id){
            if(id == id_digit_change){
                id_digit_change *= 10;
                id_str_len++;
            }
            (*table_ptr)[0] = malloc(id_str_len* sizeof(char*));
            sprintf(*table_ptr[0], "%d", id);
            (*table_ptr)[1] = list_ptr->theme;
        }else{
            **table_ptr = list_ptr->theme;
        }
    }
    print_table(header, table, 1 + add_id, rows, DEFAULT_TABLE_SEPARATORS);
    free(header);
    free(table);
}

void print_book_list(book_list *list, char add_id){
    char ** header = malloc((2 + add_id) * sizeof(char*));
    if(add_id){
        header[0] = "id";
        header[1] = "name";
        header[2] = "path";
    }else{
        header[0] = "name";
        header[1] = "path";
    }
    unsigned int rows = 0;
    for(book_list *list_ptr = list; list_ptr!=NULL; list_ptr = list_ptr->next, rows++);
    // Yes, after this 100% un-optimal pass through whole list code is hyper-optimized. Reason is because I can №2
    char ***table = malloc(rows * sizeof(char**)), ***table_ptr = table;
    unsigned int id=0, id_digit_change=10;
    unsigned char id_str_len=2;
    for(book_list *list_ptr = list; list_ptr!=NULL; list_ptr = list_ptr->next, table_ptr++, id++){
        *table_ptr = malloc((1 + add_id) * sizeof(char*));
        if(add_id){
            if(id == id_digit_change){
                id_digit_change *= 10;
                id_str_len++;
            }
            (*table_ptr)[0] = malloc(id_str_len* sizeof(char*));
            sprintf(*table_ptr[0], "%d", id);
            (*table_ptr)[1] = list_ptr->this_book.book_name;
            (*table_ptr)[2] = list_ptr->this_book.book_path;
        }else{
            (*table_ptr)[0] = list_ptr->this_book.book_name;
            (*table_ptr)[1] = list_ptr->this_book.book_path;
        }
    }
    print_table(header, table, 2 + add_id, rows, DEFAULT_TABLE_SEPARATORS);
}

#define DEFAULT_LIST_CHOICE_MESSAGES "Index out of range\n", "Choice not recognised\n"

book * book_choice_dialogue(book_list *list, char *index_out_message, char *choice_not_recognised_message){
    int choice;
    choice = input_int("Input book number");
    if(errno){
        printf("%s", choice_not_recognised_message);
        errno=0;
        return NULL;
    }
    while(choice-->0 && list!=NULL){
        list = list->next;
    }
    if(!list){
        printf("%s", index_out_message);
        return NULL;
    }
    return &list->this_book;
}

void start_basic_list_submenu(themed_book_list *themed_list, char *show){
    const char *basic_submenu = "Choose option:\n"
                                "0 - exit\n"
                                "1 - show\n"
                                "2 - add to list\n"
                                "3 - remove from list\n"
                                "4 - rename\n"
                                "5 - hide/show menu items\n"
                                "6 - open book\n";
    int option = -1;
    while(option!=0){
        if(*show){
            printf("%s", basic_submenu);
        }
        option = input_int("");
        if(errno){
            printf("Not an int");
            errno=0;
            continue;
        }
        switch (option){
            case 0:
                printf("Exiting ...\n");
                break;
            case 1:
                print_book_list(themed_list->this_book_list, 1);
                break;
            case 2:
                printf("Input book name\n");
                char *name = input_string();
                printf("Input book path\n");
                char *path = input_string();
                book b = book_create(name, path);
                themed_list->this_book_list = book_list_add_book(themed_list->this_book_list, b);
                break;
            case 3:
                ;
                book *book_to_delete = book_choice_dialogue(themed_list->this_book_list, DEFAULT_LIST_CHOICE_MESSAGES);
                if(book_to_delete){
                    themed_list->this_book_list = book_list_delete_book(themed_list->this_book_list, book_to_delete->book_path);
                }
                break;
            case 4:
                ;
                book *book_to_rename = book_choice_dialogue(themed_list->this_book_list, DEFAULT_LIST_CHOICE_MESSAGES);
                if(book_to_rename){
                    printf("Write a new name\n");
                    char* new_name = input_string();
                    free(book_to_rename->book_name);
                    book_to_rename->book_name = new_name;
                }
                break;
            case 5:
                *show = !*show;
                break;
            case 6:
                ;
                book *book_to_open = book_choice_dialogue(themed_list->this_book_list, DEFAULT_LIST_CHOICE_MESSAGES);
                if(book_to_open){
                    open_book(*book_to_open);
                }
                break;
            default:
                printf("Choice not recognised\n");
        }
    }
}

themed_book_list* list_choice_dialogue(themed_book_list *themed_list, char* index_out_message, char* choice_not_recognised_message){
    int choice;
    choice = input_int("Choose list number\n");
    if(errno){
        printf("%s", choice_not_recognised_message);
        errno=0;
        return NULL;
    }
    while(choice-->0 && themed_list!=NULL){
        themed_list = themed_list->next;
    }
    if(!themed_list){
        printf("%s", index_out_message);
    }
    return themed_list;
}

void start_basic_menu(start_menu *this, themed_book_list *themed_list, read_conf conf){
    const char *basic_menu = "Choose option:\n"
                             "0 - exit\n"
                             "1 - list all lists\n"
                             "2 - list particular list\n"
                             "3 - enter list submenu\n"
                             "4 - hide/show menu items\n"
                             "5 - create new list\n"
                             "6 - delete list\n"
                             "7 - save changes\n"
                             "8 - save changes as new config\n"
                             "9 - load config\n";
    printf("Welcome user\n");
    int option = -1;
    char show_menu_list = 1, show_list_submenu_list = 1;
    while(option!=0){
        if(show_menu_list){
            printf("%s", basic_menu);
        }
        option = input_int("");
        if(errno){
            printf("Not an int");
            errno=0;
            continue;
        }
        switch (option){
            case 0:
                printf("Exiting main menu ...\n");
                break;
            case 1:
                print_theme_list(themed_list, 1);
                break;
            case 2:
                ; // fucking C switch
                themed_book_list *result = list_choice_dialogue(themed_list, DEFAULT_LIST_CHOICE_MESSAGES);
                if(result){
                    print_book_list(result->this_book_list, 1);
                }
                break;
            case 3:
                result = list_choice_dialogue(themed_list, DEFAULT_LIST_CHOICE_MESSAGES);
                if(result){
                    start_basic_list_submenu(result, &show_list_submenu_list);
                }
                break;
            case 4:
                show_menu_list = !show_menu_list;
                break;
            case 5:
                printf("Enter list name");
                char *inp2 = input_string();
                //book_list *new_list = malloc(sizeof(struct book_list));
                themed_list = themed_book_list_add_book_list(themed_list, inp2, NULL);
                break;
            case 6:
                result = list_choice_dialogue(themed_list, DEFAULT_LIST_CHOICE_MESSAGES); // code not optimal (
                if(result){
                    themed_list = themed_book_list_delete_theme(themed_list, result->theme);
                }
                break;
            case 7:
                if(this->current_conf_path==NULL){
                    printf("You don't have predefined config file, creating new ...\n");
                }else
                {
                    conf.write_config(this->current_conf_path, themed_list);
                    break;
                }
            case 8:
                printf("Input filename\n");
                char *new_path = input_string();
                conf.write_config(new_path, themed_list);
                if(this->current_conf_path){
                    free(this->current_conf_path);
                }
                this->current_conf_path = new_path;
                break;
            case 9:
                printf("Input filename\n");
                new_path = input_string();
                themed_book_list *temp = conf.read_config(new_path);
                if(temp)
                {
                    free_themed_book_list(themed_list);
                    themed_list = temp;
                    if (this->current_conf_path)
                    {
                        free(this->current_conf_path);
                    }
                    this->current_conf_path = new_path;
                }else{
                    free(new_path);
                    printf("Conf file not opened or empty\n");
                }
                break;
            default:
                printf("Choice not recognised\n");
        }
    }
}

start_menu create_basic_menu(char *initial_conf_path){
    start_menu result = {NULL, initial_conf_path, start_basic_menu};
    return result;
}