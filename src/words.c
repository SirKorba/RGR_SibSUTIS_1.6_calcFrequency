#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include "words.h"

#include <locale.h>

wchar_t *readWord(FILE *file) 
{
    int capacity = 10;
    wchar_t *word = malloc(capacity * sizeof(wchar_t));
    int length = 0;
    wint_t c;

    while ((c = fgetwc(file)) != WEOF)
    {
        if (iswalpha(c))
        {
            if (length + 1 >= capacity)
            {
                capacity *= 2;
                word = realloc(word, capacity * sizeof(wchar_t));
            }
            word[length++] = towlower(c);
        } 
        else if (length > 0)
        {
            break;
        }
    }

    if (length == 0 && c == WEOF)
    {
        free(word);
        return NULL;
    }

    word[length] = L'\0';
    return word;
}