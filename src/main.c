#include <stdio.h>
#include <stdlib.h>
#include "menu/start_menu.h"
#include "book/reading_list.h"
#include "IO/read_configurations.h"

int main()
{
    init_logger(DEBUG, "log.txt");
    write_log(INFO, "Program start");

    start_menu menu = create_basic_menu(NULL);
    read_conf read_config = create_read_conf_txt();
    themed_book_list themes;

    menu.start_menu(&menu, NULL, read_config);

    write_log(INFO, "Program end");
}