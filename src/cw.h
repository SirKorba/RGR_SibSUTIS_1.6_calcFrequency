#include <ctype.h>

#ifndef CW_H
#define CW_H

#define MSIZE_WORD 30

typedef struct {
    wchar_t word[MSIZE_WORD];
    int count;
} CountWord;

int cw_research(CountWord *mas, size_t size,  wchar_t *word);
void cw_swap(CountWord *el1, CountWord *el2);
void cw_sort(CountWord *mas, size_t size);

#endif