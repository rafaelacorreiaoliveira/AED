/******************************************************************************
 * (c) 2010-2020 IST AED Team
 * Last modified: abl 2020-04-21
 *
 * NAME
 *   sortwords.c
 *
 * DESCRIPTION
 *   Main program for unique word finding and sorting with tables
 *
 * COMMENTS
 *   Code for preliminary distribution, to be completed
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "word.h"

enum sort_order
{
    ascending,
    descending
};

enum sort_criteria
{
    alphabetic,
    length,
    occurrences
};
#define eq(A, B) (!less(A, B) && !less(B, A))
#define exch(A, B)  \
    {               \
        Item t = A; \
        A = B;      \
        B = t;      \
    }

int OP_CNT = 0; /* global variable, to simplify complexity assessment */
void quicksort(Item a[], int l, int r, int (*less)(Item, Item));

/******************************************************************************
 * sort ()
 *
 * Arguments: a - table of items to sort
 *            l, r - limits on table to consider
 *            less - item comparison function
 * Returns: (void)
 * Side-Effects: table is sorted in place
 *
 * Description: implements "some" sorting algorithm for abstract type (Item),
 *       using also an abstract type comparison function (*less)
 *           a[] - array of abstract type Item to be sorted
 *           l - index of first element in the array to be sorted
 *           r - last element of the array to be sorted
 *           (*less)(Item,Item) - abstract type comparison function
 *****************************************************************************/
void quicksort(Item a[], int l, int r, int (*less)(Item, Item))
{
    int i, j, k, p, q;
    Item v;
    OP_CNT += 2; /*below*/
    if (r <= l)
        return;
    v = a[r];
    i = l - 1;
    j = r;
    p = l - 1;
    q = r;
    OP_CNT += 5; /*above reads and moves*/
    for (;;)
    {
        while (less(a[++i], v))
        {
            OP_CNT += 3; /*read i, a[i], v*/
            if (i == r)
                break;
        }
        while (less(v, a[--j]))
        {
            OP_CNT += 3; /*read j, a[j], v*/
            OP_CNT += 2; /*read and compare j and l*/
            if (j == l)
                break;
        }
        OP_CNT += 2; /*below*/
        if (i >= j)
            break;
        OP_CNT += 2; /*below*/
        exch(a[i], a[j]);
        if (eq(a[i], v))
        {
            OP_CNT += 4;
            p++;
            exch(a[p], a[i]);
        }
        if (eq(v, a[j]))
        {
            OP_CNT += 4;
            q--;
            exch(a[q], a[j]);
        }
    }

    exch(a[i], a[r]);
    j = i - 1;
    i = i + 1;
    OP_CNT += 5; /*above plus first read below*/
    for (k = l; k <= p; k++, j--)
    {
        OP_CNT += 3; /*read and compare in for plus exchange*/
        exch(a[k], a[j]);
    }
    OP_CNT += 1; /*first read below*/
    for (k = r - 1; k >= q; k--, i++)
    {
        OP_CNT += 3;
        exch(a[k], a[i]);
    }
    quicksort(a, l, j, less);
    quicksort(a, i, r, less);
}

/******************************************************************************
* main ()
*
*****************************************************************************/

int main(int argc, char **argv)
{
    int TnumWords;   /* total number of words in input file */
    int numWords;    /* number of distint words in input file */
    Tabword tabword; /* table holding the structure */

    /* default initialization for alfabetic order and ascending */
    enum sort_criteria criterio = alphabetic;
    enum sort_order sentido = ascending;
    char *file = argv[1];

    argv++; /* get past prog and file names */
    while (*(++argv))
    {
        if (strcmp(*argv, "-alfabetica") == 0)
            criterio = alphabetic;
        else if (strcmp(*argv, "-ocorrencias") == 0)
            criterio = occurrences;
        else if (strcmp(*argv, "-comprimento") == 0)
            criterio = length;
        else if (strcmp(*argv, "-a") == 0)
            sentido = ascending;
        else if (strcmp(*argv, "-d") == 0)
            sentido = descending;
        else
        {
            fprintf(stderr, "Wrong arguments\n");
            exit(3);
        }
    }
    TnumWords = AllocWordArray(&tabword, file);
    printf("Total number of words: %d\n", TnumWords);

    numWords = FillInWordArray(tabword, file);
    printf("Number of different words = %d\n", numWords);

    OP_CNT = 0;

    /*  Call the sorting function using as argument the
       appropriate comparison function selected by user option */

    if ((criterio == alphabetic) && (sentido == ascending))
    {
        quicksort((Item)tabword, 0, numWords - 1, &LessAlphabetic);
    }
    if ((criterio == alphabetic) && (sentido == descending))
    {
        quicksort((Item)tabword, 0, numWords - 1, &MaisAlphabetic);
    }
    if ((criterio == occurrences) && (sentido == ascending))
    {
        quicksort((Item)tabword, 0, numWords - 1, &OcuUp);
    }
    if ((criterio == occurrences) && (sentido == descending))
    {
        quicksort((Item)tabword, 0, numWords - 1, &OcuDown);
    }
    if ((criterio == length) && (sentido == ascending))
    {
        quicksort((Item)tabword, 0, numWords - 1, &CompUp);
    }
    if ((criterio == length) && (sentido == descending))
    {
        quicksort((Item)tabword, 0, numWords - 1, &CompDown);
    }

    /* ---------------------------------------- */
    printf("Accesses count for sort: %d\n", OP_CNT);
    WriteFile(tabword, file, numWords);
    FreeWordArray(&tabword, numWords);

    return 0;
}
