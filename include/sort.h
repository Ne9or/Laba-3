#ifndef SORT_H
#define SORT_H

#include "deque.h"


typedef int (*Comparator)(const Record*, const Record*);


void gnome_sort(Deque* deque, Comparator cmp);

#endif
