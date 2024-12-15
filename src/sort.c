#include "../include/sort.h"

void gnome_sort(Deque* deque, Comparator cmp) {
    size_t index = 0;
    while (index < deque->size) {
        if (index == 0 || cmp(deque_get(deque, index), deque_get(deque, index - 1)) >= 0) {
            index++;
        } else {
            deque_swap(deque, index, index - 1);
            index--;
        }
    }
}
