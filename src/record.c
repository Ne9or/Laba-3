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

bool record_read(FILE* file, Record* record) {
    char developer[64];
    char neighborhood[64];
    char type_str[16];
    int build_year;
    char has_elevator_str[4];
    char has_garbage_chute_str[4];
    int flat_count;
    int floor_count;
    double avg_flat_area;

    if (fscanf(file, "%63[^,],%63[^,],%15[^,],%d,%3[^,],%3[^,],%d,%d,%lf\n",
               developer, neighborhood, type_str, &build_year,
               has_elevator_str, has_garbage_chute_str, &flat_count,
               &floor_count, &avg_flat_area) != 9) {
        return false;
    }

    record->type = building_type_to_string(type_str);
    record->has_elevator = strcmp(has_elevator_str, "YES") == 0;
    record->has_garbage_chute = strcmp(has_garbage_chute_str, "YES") == 0;

    record_init(record, developer, neighborhood, record->type, build_year,
                record->has_elevator, record->has_garbage_chute, flat_count,
                floor_count, avg_flat_area);

    return true;
}

void record_write(FILE* file, const Record* record) {
    fprintf(file, "%s,%s,%s,%d,%s,%s,%d,%d,%.2lf\n",
            record->developer,
            record->neighborhood,
            building_type_to_string(record->type),
            record->build_year,
            record->has_elevator ? "YES" : "NO",
            record->has_garbage_chute ? "YES" : "NO",
            record->flat_count,
            record->floor_count,
            record->avg_flat_area);
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

// const char* building_type_to_string(BuildingType type) {
//     switch (type) {
//         case BUILDING_TYPE_PANEL:
//             return "PANEL";
//         case BUILDING_TYPE_BRICK:
//             return "BRICK";
//         case BUILDING_TYPE_MONOLITH:
//             return "MONOLITH";
//         default:
//             return "UNKNOWN";
//     }
// }
