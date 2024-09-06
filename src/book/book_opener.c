//
// Created by kosenko on 9/6/24.
//

#include <unistd.h>
#include "book_opener.h"
#include "log.h"
#include <string.h>

void open_book(book this_book){
    char *command_name = "okular";
    pid_t pid = fork();
    if(pid == -1){
        write_log(FATAL, "can't fork process");
    }
    else{
        if(pid == 0)
        {
            int book_path_len = strlen(this_book.book_path);
            char *book_name_formated = calloc(book_path_len + 1, sizeof(char));
            book_name_formated[0] = '"';
            stpcpy(book_name_formated + 1, this_book.book_path);
            book_name_formated[book_path_len + 1] = '"';
            book_name_formated[book_path_len + 2] = '\0';
            if (execl("/usr/bin/okular", command_name, this_book.book_path, NULL) == -1)
            {
                write_log(FATAL, "can't open book");
            }
            free(book_name_formated);
        }
    }
}
