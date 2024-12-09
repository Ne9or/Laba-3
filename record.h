#ifndef RECORD_H
#define RECORD_H

#include <stdbool.h>

// Перечисление для типов дома
typedef enum {
    PANEL,
    BRICK,
    MONOLITH
} BuildingType;

// Структура многоквартирного дома
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

// Функция для преобразования BuildingType в строку
const char* building_type_to_string(BuildingType type);

// Функция для преобразования строки в BuildingType
BuildingType string_to_building_type(const char* str);

#endif // RECORD_H
