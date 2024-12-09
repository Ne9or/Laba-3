#ifndef SORT_H
#define SORT_H

#include "deque.h"

// Тип компаратора
typedef int (*Comparator)(const Record*, const Record*);

// Гномья сортировка
void gnome_sort(Deque* deque, Comparator cmp);

#endif // SORT_H
