//
// Created by kosenko on 9/8/24.
//

#include "read_keys.h"
#include <stdio.h>

void start_read_process_keys(key_processing_callbacks callbacks)
{
    int c;
    if ((c = getchar()) > 27 || c == '\n')
    {
        if (callbacks.process_char)
        {
            callbacks.process_char((char)c, callbacks.args);
        }
    }
    else if (c < 27)
    {
        if (callbacks.process_ctrl)
        {
            callbacks.process_ctrl((char)c, callbacks.args);
        }
    }
    else
    {
        getchar();
        arrow_key arrow = getchar() - 'A';
        if (callbacks.process_arrow)
        {
            callbacks.process_arrow(arrow, callbacks.args);
        }
    }
}