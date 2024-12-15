#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>

void generate_mode(int count, const char* output_file);
void sort_mode(const char* input_file, const char* output_file, bool ascending);
void print_mode(const char* input_file, const char* output_file);
void combined_mode(const char* input_file, const char* output_file, bool ascending);

#endif