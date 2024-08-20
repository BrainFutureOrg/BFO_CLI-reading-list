//
// Created by maximus on 04.07.23.
//

#ifndef CONSOLE_CODE_EDITOR_TEST_TEST_FUNCS_H
#define CONSOLE_CODE_EDITOR_TEST_TEST_FUNCS_H

#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#if __has_include("../terminal_bfo/colors_bfo/colors.h")
#include "../terminal_bfo/colors_bfo/colors.h"
#define HAS_BFO_COLORS
#endif
//#include "../prj_error.h"
#if __has_include("../terminal_bfo/colors_bfo/colors.h")
#include "../loging_bfo//log.h"
#define HAS_BFO_LOGGING
#endif

#define START_MULTITEST char old_successfully = test_success; \
                        test_success = 1;                     \


#define END_MULTITEST(func_name, unsuccess_text, ...) if(!test_success) \
                                                    {                 \
                                                        color_from_parts_printf(DEFAULT | FOREGROUND_RED, unsuccess_text, __VA_ARGS__);                  \
                                                    } \
                                                    else                \
                                                    {                   \
                                                        color_from_parts_printf(DEFAULT | FOREGROUND_GREEN, "Test \"%s\" success\n", func_name);                \
                                                        test_success = old_successfully;                    \
                                                    }
extern char test_success;
void assertEqual(void *first,
                 void *second,
                 char (*equal_function)(void *first, void *second),
                 char *test_name,
                 char *text_error_formated,
                 ...);
void assertNotEqual(void *first,
                    void *second,
                    char (*equal_function)(void *first, void *second),
                    char *test_name,
                    char *text_error_formated,
                    ...);

void print_test_success();

void assertEqual_log(void *first,
                     void *second,
                     char (*equal_function)(void *first, void *second),
                     char *test_name,
                     char *ftext_error,
                     ...);
void assertNotEqual_log(void *first,
                        void *second,
                        char (*equal_function)(void *first, void *second),
                        char *test_name,
                        char *ftext_error,
                        ...);

#endif //CONSOLE_CODE_EDITOR_TEST_TEST_FUNCS_H
