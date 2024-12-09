#ifndef DEQUE_H
#define DEQUE_H

#include "record.h"
#include <stddef.h>
#include <stdbool.h>

// Узел для двухсторонней очереди
typedef struct Node {
    Record data;
    struct Node* next;
    struct Node* prev;
} Node;

// Структура двухсторонней очереди
typedef struct {
    Node* head; // Указатель на начало
    Node* tail; // Указатель на конец
    size_t size; // Количество элементов
} Deque;

// Инициализация
void deque_init(Deque* deque);

// Получение размера
size_t deque_size(const Deque* deque);

// Получение элемента по индексу
Record* deque_get(Deque* deque, size_t index);

// Получение указателей
Record* deque_begin(Deque* deque);
Record* deque_end(Deque* deque);

// Добавление элемента
void deque_push_front(Deque* deque, Record data);
void deque_push_back(Deque* deque, Record data);
void deque_insert(Deque* deque, size_t index, Record data);

// Удаление элемента
void deque_pop_front(Deque* deque);
void deque_pop_back(Deque* deque);
void deque_erase(Deque* deque, size_t index);

// Замена элементов
void deque_swap(Deque* deque, size_t index1, size_t index2);

// Очистка
void deque_clear(Deque* deque);

#endif // DEQUE_H
