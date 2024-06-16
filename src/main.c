#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include "cw.h"                                                                     //header file for working with CountWords objects
#include "words.h"                                                                  //header file for working with words

#define CAPACITY 2                                                                  //start size for array with CountWords objects

int check_input(int narg, char **args);                                             //function for check_input
void CalcFrequency(char *input_filename, char *output_filename);

int main(int narg, char *args[]) {

    setlocale(LC_ALL, "");

    int nerror = check_input(narg, args);                                           //result of check_input

    if (nerror) {                                                                   //check_input
        return nerror;
    }
                                       
    char *input_filename = malloc(sizeof(char) * (strlen(args[1]) + 1));
    sprintf(input_filename, "%s", args[1]);
    char *output_filename = malloc(sizeof(char) * (strlen(args[2]) + 1));
    sprintf(output_filename, "%s", args[2]);

    CalcFrequency(input_filename, output_filename);                                //run func

    return 0;
}

int check_input(int narg, char **args) {
    if (narg < 3) {
        fprintf(stderr, "Error: not enough number of input arguments\n");
        return 1;
    } else if (narg > 3) {
        fprintf(stderr, "Error: too many number of input arguments\n");
        return 5;
    } else if (fopen(args[1], "r") == NULL) {
        fprintf(stderr, "Error: not found an input file\n");
        return 2;
    } else if (fopen(args[2], "w") == NULL) {
        fprintf(stderr, "Error: not created an output file\n");
        return 3;
    }

    return 0;
}

void CalcFrequency(char *input_filename, char *output_filename)
{
    size_t size = CAPACITY;
    CountWord *words = malloc(sizeof(CountWord) * size);

    wchar_t *word = malloc(sizeof(wchar_t) * MSIZE_WORD);

    FILE *input_file = fopen(input_filename, "r");
    FILE *output_file;

    word = readWord(input_file);
    if (word == NULL) {
        fprintf(stderr, "Error: Input file is empty or not stated letters\n");
        free(word);
        return;
    }
    wcscpy(words[0].word, word);
    words[0].count = 1;

    for (word = readWord(input_file); word; word = readWord(input_file)) {
        int index = cw_research(words, size, word);
        if (index >= 0) {
            words[index].count++;
        } else {
            if (wcslen(word) > 1) {
                wcscpy(words[size - 1].word, word);
                words[size - 1].count = 1;
                size++;
                words = realloc(words, sizeof(CountWord) * size);
            }
        }
    }

    fclose(input_file);

    output_file = fopen(output_filename, "w");

    for (int i = 0; i < size - 1; i++) {
        cw_sort(words, size);
        if (words[i].count > 1)
            fwprintf(output_file, L"%ls - %d\n", words[i].word, words[i].count);
    }

    fclose(output_file);

    free(words);
    free(word);
}