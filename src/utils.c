#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/record.h"
#include "../include/deque.h"
#include "../include/sort.h"


const char* building_type_to_string(BuildingType type) {
    switch (type) {
        case BUILDING_TYPE_PANEL:
            return "PANEL";
        case BUILDING_TYPE_BRICK:
            return "BRICK";
        case BUILDING_TYPE_MONOLITH:
            return "MONOLITH";
        default:
            return "UNKNOWN";
    }
}

// //comparisons
// int compare_asc(const Record* a, const Record* b) {
//     return a->build_year - b->build_year;
// }

// int compare_desc(const Record* a, const Record* b) {
//     return b->build_year - a->build_year;
// }

//generate
void generate_mode(int count, const char* output_file) {
    FILE* out = output_file ? fopen(output_file, "w") : stdout;
    if (!out) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    BuildingType types[] = {BUILDING_TYPE_PANEL, BUILDING_TYPE_BRICK, BUILDING_TYPE_MONOLITH};

    for (int i = 0; i < count; i++) {
        Record record;
        snprintf(record.developer, sizeof(record.developer), "Developer_%d", i);
        snprintf(record.neighborhood, sizeof(record.neighborhood), "Neighborhood_%d", i);

        record.type = types[rand() % 3];
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
    char* record_type = malloc(9*sizeof(char));
    char* has_elevator_str = malloc(3*sizeof(char));
    char* has_garbage_chute_str = malloc(3*sizeof(char));
    while (fgets(line, sizeof(line), in)) {
        Record record;
        sscanf(line, "%49[^,],%49[^,],%9[^,],%d,%3[^,],%3[^,],%d,%d,%lf",
               record.developer, record.neighborhood,
               record_type, &record.build_year,
               has_elevator_str,
               has_garbage_chute_str,
               &record.flat_count, &record.floor_count, &record.avg_flat_area);
        record.type = string_to_building_type(record_type); 
        record.has_elevator = strcmp(has_elevator_str, "YES") == 0;
        record.has_garbage_chute = strcmp(has_garbage_chute_str, "YES") == 0;
 
        deque_push_back(&deque, record);
    }

    if (input_file) fclose(in);

    
    gnome_sort(&deque, ascending ? record_compare : record_compare);

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
