#ifndef DEQUE_H
#define DEQUE_H

#include "record.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct Node {
    Record data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    size_t size;
} Deque;

void deque_init(Deque* deque);

// size
size_t deque_size(const Deque* deque);

// element by id
Record* deque_get(Deque* deque, size_t index);

// pointer
Record* deque_begin(Deque* deque);
Record* deque_end(Deque* deque);

// add
void deque_push_front(Deque* deque, Record data);
void deque_push_back(Deque* deque, Record data);
void deque_insert(Deque* deque, size_t index, Record data);

// delete
void deque_pop_front(Deque* deque);
void deque_pop_back(Deque* deque);
void deque_erase(Deque* deque, size_t index);

void deque_swap(Deque* deque, size_t index1, size_t index2);

void deque_clear(Deque* deque);

#endif
