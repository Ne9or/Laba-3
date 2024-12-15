#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/record.h"
#include "../include/deque.h"
#include "../include/sort.h"


//comparisons
int compare_asc(const Record* a, const Record* b) {
    return a->build_year - b->build_year;
}

int compare_desc(const Record* a, const Record* b) {
    return b->build_year - a->build_year;
}
// combined mode
// void combined_mode(const char* input_file, const char* output_file, bool ascending) {
//     FILE* in = fopen(input_file, "r");
//     if (!in) {
//         perror("Error opening input file");
//         exit(EXIT_FAILURE);
//     }

//     Deque deque;
//     deque_init(&deque);

//     char line[256];
//     while (fgets(line, sizeof(line), in)) {
//         Record record;
//         sscanf(line, "%49[^,],%49[^,],%9[^,],%d,%3[^,],%3[^,],%d,%d,%lf",
//                record.developer, record.neighborhood,
//                (char*)&record.type, &record.build_year,
//                (char*)&record.has_elevator,
//                (char*)&record.has_garbage_chute,
//                &record.flat_count, &record.floor_count, &record.avg_flat_area);
//         deque_push_back(&deque, record);
//     }

//     fclose(in);

//     gnome_sort(&deque, ascending ? compare_asc : compare_desc);

//     FILE* out = fopen(output_file, "w");
//     if (!out) {
//         perror("Error opening output file");
//         exit(EXIT_FAILURE);
//     }

//     Node* node = deque.head;
//     while (node) {
//         Record* record = &node->data;
//         fprintf(out, "%s,%s,%s,%d,%s,%s,%d,%d,%.2f\n",
//                 record->developer,
//                 record->neighborhood,
//                 building_type_to_string(record->type),
//                 record->build_year,
//                 record->has_elevator ? "YES" : "NO",
//                 record->has_garbage_chute ? "YES" : "NO",
//                 record->flat_count,
//                 record->floor_count,
//                 record->avg_flat_area);
//         node = node->next;
//     }

//     fclose(out);
//     deque_clear(&deque);
// }

//generate
void generate_mode(int count, const char* output_file) {
    FILE* out = output_file ? fopen(output_file, "w") : stdout;
    if (!out) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; i++) {
        Record record;
        snprintf(record.developer, sizeof(record.developer), "Developer_%d", i);
        snprintf(record.neighborhood, sizeof(record.neighborhood), "Neighborhood_%d", i);
        record.type = i % 3;
        record.build_year = 1950 + rand() % 75;
        record.has_elevator = rand() % 2;
        record.has_garbage_chute = rand() % 2;
        record.flat_count = 50 + rand() % 151;
        record.floor_count = 5 + rand() % 26;
        record.avg_flat_area = 40.0 + (rand() % 1001) / 10.0;

        fprintf(out, "%s,%s,%s,%d,%s,%s,%d,%d,%.2f\n",
                record.developer,
                record.neighborhood,
                building_type_to_string(record.type),
                record.build_year,
                record.has_elevator ? "YES" : "NO",
                record.has_garbage_chute ? "YES" : "NO",
                record.flat_count,
                record.floor_count,
                record.avg_flat_area);
    }

    if (output_file) fclose(out);
}

// sort
void sort_mode(const char* input_file, const char* output_file, bool ascending) {
    Deque deque;
    deque_init(&deque);

    FILE* in = input_file ? fopen(input_file, "r") : stdin;
    if (!in) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    // read
    char line[256];
    while (fgets(line, sizeof(line), in)) {
        Record record;
        sscanf(line, "%49[^,],%49[^,],%9[^,],%d,%3[^,],%3[^,],%d,%d,%lf",
               record.developer, record.neighborhood,
               (char*)&record.type, &record.build_year,
               (char*)&record.has_elevator,
               (char*)&record.has_garbage_chute,
               &record.flat_count, &record.floor_count, &record.avg_flat_area);
        deque_push_back(&deque, record);
    }

    if (input_file) fclose(in);

    // gnome sort
    gnome_sort(&deque, ascending ? compare_asc : compare_desc);

    FILE* out = output_file ? fopen(output_file, "w") : stdout;
    if (!out) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    // sorted output
    Node* node = deque.head;
    while (node) {
        Record* record = &node->data;
        fprintf(out, "%s,%s,%s,%d,%s,%s,%d,%d,%.2f\n",
                record->developer,
                record->neighborhood,
                building_type_to_string(record->type),
                record->build_year,
                record->has_elevator ? "YES" : "NO",
                record->has_garbage_chute ? "YES" : "NO",
                record->flat_count,
                record->floor_count,
                record->avg_flat_area);
        node = node->next;
    }

    if (output_file) fclose(out);
    deque_clear(&deque);
}

// data print
void print_mode(const char* input_file, const char* output_file) {
    FILE* in = input_file ? fopen(input_file, "r") : stdin;
    FILE* out = output_file ? fopen(output_file, "w") : stdout;

    if (!in) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    if (!out) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), in)) {
        fprintf(out, "%s", line);
    }

    if (input_file) fclose(in);
    if (output_file) fclose(out);
}
