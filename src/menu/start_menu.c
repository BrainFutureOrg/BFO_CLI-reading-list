#include "start_menu.h"
#include <stdio.h>
#include <string.h>

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
        for(unsigned int i = 0; i<*col_width_ptr; i--){
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

#define DEFAULT_TABLE_SEPARATORS "|", '-', ""

void print_theme_list(themed_book_list *list, char add_id){
    char ** header = malloc((1 + add_id) * sizeof(char*));
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
            *table_ptr[0] = malloc(id_str_len* sizeof(char*));
            sprintf(*table_ptr[0], "%d", id);
            *table_ptr[1] = list_ptr->theme;
        }else{
            **table_ptr = list_ptr->theme;
        }
    }
    print_table(header, table, 1 + add_id, rows, DEFAULT_TABLE_SEPARATORS);
}

void print_book_list(book_list *list, char add_id){
    char ** header = malloc((2 + add_id) * sizeof(char*));
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
            *table_ptr[0] = malloc(id_str_len* sizeof(char*));
            sprintf(*table_ptr[0], "%d", id);
            *table_ptr[1] = list_ptr->this_book.book_name;
            *table_ptr[2] = list_ptr->this_book.book_path;
        }else{
            *table_ptr[0] = list_ptr->this_book.book_name;
            *table_ptr[1] = list_ptr->this_book.book_path;
        }
    }
    print_table(header, table, 2 + add_id, rows, DEFAULT_TABLE_SEPARATORS);
}

void start_basic_list_submenu(book_list *list, char *show){
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
        scanf("%d", &option);//TODO NO scanf
        switch (option){ //TODO implement 2,3,4,6
            case 0:
                printf("Exiting ...");
                break;
            case 1:
                print_book_list(list, 1);
                break;

            case 5:
                *show = !*show;
                break;
            default:
                printf("Choice not recognised");
        }
    }
}

#define DEFAULT_LIST_CHOICE_MESSAGES "Index out of range\n", "Choice not recognised\n"

themed_book_list* list_choice_dialogue(themed_book_list *themed_list, char* index_out_message, char* choice_not_recognised_message){
    unsigned int choice;
    scanf("%d", &choice);//TODO no scanf
    while(choice-->0 && themed_list!=NULL){
        themed_list = themed_list->next;
    }
    if(!themed_list){
        printf("%s", index_out_message);
    }
    return themed_list;
}

void start_basic_menu(start_menu *this, themed_book_list *themed_list, read_conf conf, void* additional_data){
    const char *basic_menu = "Choose option:\n"
                             "0 - exit\n"
                             "1 - list all lists\n"
                             "2 - list particular list\n"
                             "3 - enter list submenu\n"
                             "4 - hide/show menu items\n"
                             "5 - create new list\n"
                             "6 - delete list\n"
                             "7 - save changes\n"
                             "8 - save changes as new config\n";
    printf("Welcome user\n");
    int option = -1;
    char show_menu_list = 1, show_list_submenu_list = 1;
    while(option!=0){
        if(show_menu_list){
            printf("%s", basic_menu);
        }
        scanf("%d", &option);//TODO NO scanf
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
                    start_basic_list_submenu(result->this_book_list, &show_list_submenu_list);
                }
                break;
            case 4:
                option = !option;
                break;
            case 5:
                printf("Enter list name");
                char *dummy_input = "f";//TODO make actual input with io lib
                book_list *new_list = malloc(sizeof(struct book_list));
                themed_book_list_add_book_list(themed_list, dummy_input, new_list);
                break;
            case 6:
                result = list_choice_dialogue(themed_list, DEFAULT_LIST_CHOICE_MESSAGES); // code not optimal (
                if(result){
                    themed_book_list_delete_theme(themed_list, result->theme);
                }
                break;
            case 7:
                if(this->current_conf_path==NULL){
                    //TODO input new path
                }
                conf.write_config(this->current_conf_path, themed_list);
                break;
            case 8:
                ;
                char *new_path = "dummy_path";//TODO actual IO
                conf.write_config(new_path, themed_list);
            default:
                printf("Choice not recognised\n");
        }
    }
}

start_menu create_basic_menu(char *initial_conf_path){
    start_menu result = {NULL, initial_conf_path, start_basic_menu};
    return result;
}