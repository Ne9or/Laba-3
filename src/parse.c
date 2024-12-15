#include "../include/parse.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// parse arguments
void parse_arguments(int argc, char* argv[]) {
    bool generate_flag = false;
    int generate_count = 0;
    bool sort_flag = false;
    bool print_flag = false;
    char* input_file = NULL;
    char* output_file = NULL;
    bool ascending = true;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--generate") == 0 || strcmp(argv[i], "-g") == 0) {
            if (i + 1 < argc) {
                generate_flag = true;
                generate_count = atoi(argv[++i]);
            } else {
                fprintf(stderr, "Error: Missing argument for --generate\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "--sort") == 0 || strcmp(argv[i], "-s") == 0) {
            sort_flag = true;
        } else if (strcmp(argv[i], "--print") == 0 || strcmp(argv[i], "-P") == 0) {
            print_flag = true;
        } else if (strncmp(argv[i], "--in=", 5) == 0) {
            input_file = argv[i] + 5;
        } else if (strncmp(argv[i], "--out=", 6) == 0) {
            output_file = argv[i] + 6;
        } else if (strncmp(argv[i], "--type=", 7) == 0) {
            char* type = argv[i] + 7;
            if (strcmp(type, "asc") == 0 || strcmp(type, "A") == 0) {
                ascending = true;
            } else if (strcmp(type, "desc") == 0 || strcmp(type, "D") == 0) {
                ascending = false;
            } else {
                fprintf(stderr, "Error: Invalid sort type '%s'\n", type);
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "Error: Unknown argument '%s'\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    // flag operations

    if (generate_flag && sort_flag) {
        generate_mode(generate_count, input_file);
        sort_mode(input_file, output_file, ascending);
        //combined_mode(input_file, output_file, ascending);
    } else if (generate_flag) {
        generate_mode(generate_count, output_file);
    } else if (sort_flag) {
        sort_mode(input_file, output_file, ascending);
    } else if (print_flag) {
        print_mode(input_file, output_file);
    } else {
        fprintf(stderr, "Error: No mode specified (--generate, --sort, or --print)\n");
        exit(EXIT_FAILURE);
    }
}
