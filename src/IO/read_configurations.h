//
// Created by maksym on 8/20/24.
//

#ifndef BFO_CLI_READING_LIST_SRC_IO_READ_CONFIGURATIONS_H
#define BFO_CLI_READING_LIST_SRC_IO_READ_CONFIGURATIONS_H
#include "../book/reading_list.h"
#include "../library/loging_bfo/log.h"

typedef struct config_options
{
    themed_book_list (*read_config)(char *path);
    void (*write_config)(char *path, themed_book_list *list);
} read_conf;

#endif //BFO_CLI_READING_LIST_SRC_IO_READ_CONFIGURATIONS_H
