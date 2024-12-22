#include "../include/record.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void record_init(Record* record, const char* developer, const char* neighborhood,
                 BuildingType type, int build_year, bool has_elevator,
                 bool has_garbage_chute, int flat_count, int floor_count,
                 double avg_flat_area) {
    strncpy(record->developer, developer, sizeof(record->developer) - 1);
    record->developer[sizeof(record->developer) - 1] = '\0';

    strncpy(record->neighborhood, neighborhood, sizeof(record->neighborhood) - 1);
    record->neighborhood[sizeof(record->neighborhood) - 1] = '\0';
    record->type = type;
    record->build_year = build_year;
    record->has_elevator = has_elevator;
    record->has_garbage_chute = has_garbage_chute;
    record->flat_count = flat_count;
    record->floor_count = floor_count;
    record->avg_flat_area = avg_flat_area;
}

int record_compare(const Record* a, const Record* b, bool ascending) {
    int result = a->build_year - b->build_year;
    return ascending ? result : -result;
}

BuildingType string_to_building_type(const char* type_str) {
       if (strcmp(type_str, "PANEL") == 0) {
           return BUILDING_TYPE_PANEL;
       } else if (strcmp(type_str, "BRICK") == 0) {
           return BUILDING_TYPE_BRICK;
       } else if (strcmp(type_str, "MONOLITH") == 0) {
           return BUILDING_TYPE_MONOLITH;
       }
       fprintf(stderr, "Error: Unknown building type '%s'\n", type_str);
       exit(EXIT_FAILURE);
}
