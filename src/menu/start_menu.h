#ifndef BFO_CLI_READING_LIST_SRC_IO_START_MENU
#define BFO_CLI_READING_LIST_SRC_IO_START_MENU

#include "../book/reading_list.h"
#include "../IO/read_configurations.h"

// Adapter struct for UI starting
typedef struct start_menu{
    void *additional_data; //because user may have whatever configs and UI
    char *current_conf_path;
    void (*start_menu)(struct start_menu *this, themed_book_list *themed_list, read_conf conf);

}start_menu;

start_menu create_basic_menu(char *initial_conf_path);

#endif