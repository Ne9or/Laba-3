#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "record.h"
#include "deque.h"
#include "sort.h"

// Прототипы функций для обработки режимов
void generate_mode(int count, const char* output_file);
void sort_mode(const char* input_file, const char* output_file, bool ascending);
void print_mode(const char* input_file, const char* output_file);

// Компараторы для сортировки
int compare_asc(const Record* a, const Record* b) {
    return a->build_year - b->build_year; // Пример сортировки по году постройки
}

int compare_desc(const Record* a, const Record* b) {
    return b->build_year - a->build_year;
}

// Разбор аргументов командной строки
void parse_arguments(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: app [--generate N] [--sort] [--print] [options]\n");
        exit(EXIT_FAILURE);
    }

    bool generate_flag = false, sort_flag = false, print_flag = false;
    int generate_count = 0;
    char* input_file = NULL;
    char* output_file = NULL;
    bool ascending = true;

    // Разбор аргументов
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

    // Выполнение соответствующего режима
    if (generate_flag) {
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

// Генерация случайных данных
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
        record.type = i % 3; // Чередуем типы
        record.build_year = 1980 + rand() % 40;
        record.has_elevator = rand() % 2;
        record.has_garbage_chute = rand() % 2;
        record.flat_count = 50 + rand() % 150;
        record.floor_count = 5 + rand() % 25;
        record.avg_flat_area = 40.0 + (rand() % 1000) / 10.0;

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

// Сортировка данных
void sort_mode(const char* input_file, const char* output_file, bool ascending) {
    Deque deque;
    deque_init(&deque);

    FILE* in = input_file ? fopen(input_file, "r") : stdin;
    if (!in) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    // Чтение данных
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

    // Сортировка
    gnome_sort(&deque, ascending ? compare_asc : compare_desc);

    FILE* out = output_file ? fopen(output_file, "w") : stdout;
    if (!out) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    // Вывод отсортированных данных
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

// Печать данных
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
        fprintf(out, "%s", line); // Просто выводим данные в табличном формате
    }

    if (input_file) fclose(in);
    if (output_file) fclose(out);
}

int main(int argc, char* argv[]) {
    parse_arguments(argc, argv);
    return 0;
}
