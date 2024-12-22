#ifndef RECORD_H
#define RECORD_H

#include <stdbool.h>
#include <stdio.h>

typedef enum {
    BUILDING_TYPE_PANEL,
    BUILDING_TYPE_BRICK,
    BUILDING_TYPE_MONOLITH
} BuildingType;

typedef struct {
    char developer[50];
    char neighborhood[50];
    BuildingType type;
    int build_year;
    bool has_elevator;
    bool has_garbage_chute;
    int flat_count;
    int floor_count;
    double avg_flat_area;
} Record;

const char* building_type_to_string(BuildingType type);

BuildingType string_to_building_type(const char* str);

int record_compare(const Record* a, const Record* b);
#endif
