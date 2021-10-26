/******************************************************************************
* (c) 2010-2020 IST AED Team
* Last modified: abl 2020-04-21
*
* NAME
*   word.h
*
* DESCRIPTION
*   Abstract interface for word item and table data and functions
*    (word item expected to hold string pointer and int counter)
*   File reading, table building, etc. functions, in particular:
*   - AllocaTabelaPalavras() scans the file to find number of words, alloc table
*   - PreencheTabelaPalavras() re-reads file, filling table with unique words
*
* COMMENTS
*   Needs defs.h for Item definition
******************************************************************************/

#ifndef _WORD_H_
#define _WORD_H_

#include "defs.h"

typedef struct Sword Sword;
typedef struct Sword **Tabword;

char *ReadWord(FILE *f);
FILE *OpenFile(char *name, char *mode);

void ExitMemError(int k);
int AllocWordArray(Tabword *t, char *file);
int NewWord(Tabword t, char *word, int numWords);
int FillInWordArray(Tabword t, char *file);
void WriteFile(Tabword t, char *file, int numWords);
void FreeWordArray(Tabword *t, int TnumWords);

int LessAlphabetic(Item a, Item b);
int LessNumUses(Item a, Item b);
int LessLength(Item a, Item b);
int MaisAlphabetic(Item a, Item b);
int OcuUp(Item a, Item b);
int OcuDown(Item a, Item b);
int CompUp(Item a, Item b);
int CompDown(Item a, Item b);

#endif
