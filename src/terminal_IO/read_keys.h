//
// Created by kosenko on 9/8/24.
//

#ifndef BFO_CLI_READING_LIST_SRC_TERMINAL_IO_READ_KEYS_H
#define BFO_CLI_READING_LIST_SRC_TERMINAL_IO_READ_KEYS_H

#define DEL 127

typedef enum
{
    ARROW_KEY_UP = 0,
    ARROW_KEY_DOWN = 1,
    ARROW_KEY_RIGHT = 2,
    ARROW_KEY_LEFT = 3
} arrow_key; //numbers are to ensure same values since they may be used in computation

typedef struct
{
    void
    (*process_char)(char c, void *args);
    void
    (*process_ctrl)(char c, void *args);
    void
    (*process_arrow)(arrow_key arrow, void *args);
    void *args;
} key_processing_callbacks;

void start_read_process_keys(key_processing_callbacks callbacks);

#endif //BFO_CLI_READING_LIST_SRC_TERMINAL_IO_READ_KEYS_H
