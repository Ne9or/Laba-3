#include "../include/record.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/sort.h"
#include <string.h>
#include <ctype.h>

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

 int compare_string(const char* st1, const char* st2) {
    char sym1 = '\0';
    char sym2 = '\0';
    
    if (st1 == st2){
        return 0;
    }
    char* abt = "abcdefghijklmnopqrstuvwxyz"; 
    for (int i = 0; st1[i] != '\0'; i++) { 
        if  (st2[i] == '\0') {
            return 1;
        }
        sym1 = tolower(st1[i]);
        sym2 = tolower(st2[i]);
        if (sym1 != sym2) {
            break;
        }
    }

    for (int i = 0; abt[i] != '\0'; i++) {
        if (sym1 == abt[i]){
            return 1;
        }
        if (sym2 == abt[i]) {
            return -1;
        }
    }   
    return 0;
}

int record_compare(const Record* a, const Record* b) {

    int result = 0;
    result = compare_string(a->developer, b->developer);
    if (result != 0) {
        return -result;
    }
    result = compare_string(a->neighborhood, b->neighborhood);
    if (result != 0) {
        return result;
    }
    result = compare_string(building_type_to_string(a->type), building_type_to_string(b->type));
    if (result != 0) {
        return result;
    }
    if (a->build_year > b->build_year){
        result = 1;
    } else if (a->build_year < b->build_year) {
        result = -1;
    } else  if (a->has_elevator > b->has_elevator){
        result = 1;
    } else if (a->has_elevator < b->has_elevator) {
        result = -1;
    } else if (a->has_garbage_chute > b->has_garbage_chute){
        result = 1;
    } else if (a->has_garbage_chute < b->has_garbage_chute) {
        result = -1;
    } else if (a->flat_count > b->flat_count){
        result = 1;
    } else if (a->flat_count < b->flat_count) {
        result = -1;
    } else if (a->floor_count > b->floor_count){
        result = 1;
    } else if (a->floor_count < b->floor_count) {
        result = -1;
    } else if (a->avg_flat_area > b->avg_flat_area){
        result = 1;
    } else if (a->avg_flat_area < b->avg_flat_area) {
        result = -1;
    }

    return result;
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
