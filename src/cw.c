#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include "cw.h"

int cw_research(CountWord *mas, size_t size,  wchar_t *word) {
    for (int i = 0; i < size; i++) {
        if (wcscmp(mas[i].word, word) == 0 && wcslen(word)) {
            return i;
        }
    }

    return -1;
}

void cw_swap(CountWord *el1, CountWord *el2) {
    CountWord temp;
    wcscpy(temp.word, el1->word);
    temp.count = el1->count;
    wcscpy(el1->word, el2->word);
    el1->count = el2->count;
    wcscpy(el2->word, temp.word);
    el2->count = temp.count;
}

void cw_sort(CountWord *mas, size_t size) {

    for (int i = 0; i < size - 1; i++) {

        for (int j = 0; j < size - i - 1; j++) {

            if (mas[j].count < mas[j + 1].count) {
                cw_swap(&mas[j], &mas[j + 1]);
            }
        }
    }
}