cmake_minimum_required(VERSION 3.29)
project(BFO_CLI_reading_list C)

set(CMAKE_C_STANDARD 11)

include_directories(src/library/loging_bfo)
include_directories(src/library/string_bfo)
include_directories(src/library/terminal_bfo)
include_directories(src/library/terminal_bfo/colors_bfo)
include_directories(src/library/terminal_bfo/progress_bar)
include_directories(src/library/tests_bfo)

add_executable(BFO_CLI_reading_list
        src/library/loging_bfo/log.c
        src/library/loging_bfo/log.h
        src/library/string_bfo/String_array_struct.c
        src/library/string_bfo/String_struct.c
        src/library/string_bfo/String_struct.h
        src/library/string_bfo/String_struct_formatting.c
        src/library/terminal_bfo/colors_bfo/bins.c
        src/library/terminal_bfo/colors_bfo/bins.h
        src/library/terminal_bfo/colors_bfo/colors.c
        src/library/terminal_bfo/colors_bfo/colors.h
        src/library/terminal_bfo/progress_bar/progres_bar.c
        src/library/terminal_bfo/progress_bar/progres_bar.h
        src/library/terminal_bfo/terminal_funcs.h
        src/library/tests_bfo/test_funcs.c
        src/library/tests_bfo/test_funcs.h
        src/main.c
        src/IO/read_configurations.c
        src/IO/read_configurations.h
        src/menu/start_menu.c
        src/book/reading_list.c
        src/book/reading_list.h
        src/IO/input.c
        src/IO/input.h
        src/book/book_opener.c
        src/book/book_opener.h
        src/terminal_UI/tables.c
        src/terminal_UI/tables.h
        src/terminal_IO/read_keys.c
        src/terminal_IO/read_keys.h
        src/terminal_UI/menus/char_menu.c
        src/terminal_UI/menus/char_menu.h
        src/terminal_UI/menus/table_selection_menu.c
        src/terminal_UI/menus/table_selection_menu.h)

target_link_libraries(BFO_CLI_reading_list m)