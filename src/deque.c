#include "../include/deque.h"
#include <stdlib.h>
#include <stdio.h>

void deque_init(Deque* deque) {
    deque->head = NULL;
    deque->tail = NULL;
    deque->size = 0;
}

size_t deque_size(const Deque* deque) {
    return deque->size;
}

Record* deque_get(Deque* deque, size_t index) {
    if (index >= deque->size) return NULL;
    Node* current = deque->head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return &current->data;
}

Record* deque_begin(Deque* deque) {
    return deque->head ? &deque->head->data : NULL;
}

Record* deque_end(Deque* deque) {
    return deque->tail ? &deque->tail->data : NULL;
}

void deque_push_front(Deque* deque, Record data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = deque->head;
    new_node->prev = NULL;

    if (deque->head) {
        deque->head->prev = new_node;
    }
    deque->head = new_node;

    if (!deque->tail) {
        deque->tail = new_node;
    }

    deque->size++;
}

void deque_push_back(Deque* deque, Record data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = deque->tail;

    if (deque->tail) {
        deque->tail->next = new_node;
    }
    deque->tail = new_node;

    if (!deque->head) {
        deque->head = new_node;
    }

    deque->size++;
}

void deque_insert(Deque* deque, size_t index, Record data) {
    if (index > deque->size) {
        fprintf(stderr, "Error: Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    if (index == 0) {
        deque_push_front(deque, data);
        return;
    } else if (index == deque->size) {
        deque_push_back(deque, data);
        return;
    }

    Node* current = deque->head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = current;
    new_node->prev = current->prev;

    if (current->prev) {
        current->prev->next = new_node;
    }
    current->prev = new_node;

    deque->size++;
}

void deque_pop_front(Deque* deque) {
    if (!deque->head) return;

    Node* temp = deque->head;
    deque->head = deque->head->next;

    if (deque->head) {
        deque->head->prev = NULL;
    } else {
        deque->tail = NULL;
    }

    free(temp);
    deque->size--;
}

void deque_pop_back(Deque* deque) {
    if (!deque->tail) return;

    Node* temp = deque->tail;
    deque->tail = deque->tail->prev;

    if (deque->tail) {
        deque->tail->next = NULL;
    } else {
        deque->head = NULL;
    }

    free(temp);
    deque->size--;
}

void deque_erase(Deque* deque, size_t index) {
    if (index >= deque->size) {
        fprintf(stderr, "Error: Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    if (index == 0) {
        deque_pop_front(deque);
        return;
    } else if (index == deque->size - 1) {
        deque_pop_back(deque);
        return;
    }

    Node* current = deque->head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }

    if (current->prev) {
        current->prev->next = current->next;
    }
    if (current->next) {
        current->next->prev = current->prev;
    }

    free(current);
    deque->size--;
}

void deque_swap(Deque* deque, size_t index1, size_t index2) {
    if (index1 >= deque->size || index2 >= deque->size) {
        fprintf(stderr, "Error: Index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    if (index1 == index2) return;

    Record* a = deque_get(deque, index1);
    Record* b = deque_get(deque, index2);
    Record temp = *a;
    *a = *b;
    *b = temp;
}

void deque_clear(Deque* deque) {
    while (deque->head) {
        deque_pop_front(deque);
    }
    deque->size = 0;
}
