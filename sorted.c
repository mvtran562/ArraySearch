// Matthew Tran
// Project 2: Sets and Arrays
// COEN 12
// Week 2: Sorted

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"


// define SET as struct set
typedef struct set 
{
    int count;
    int length;
    char **data;
}SET;

// Search Function
// Searches Data to see whether or not elt is in the array
// returns index of data if it is there, and returns -1 if it is not
// O(logn)
static int search(SET *sp, char *elt, bool *found)
{
    int lo;
    int hi;
    lo = 0;
    hi = sp->count -1;
    while(lo <= hi)
    {
        int mid = (lo + hi)/2;
        int cmpr = strcmp(elt,sp->data[mid]);
        if(cmpr ==0 )
        {
            *found = true;
            return mid;
        }
        if(cmpr < 0)
        {
            
            hi = mid-1;
            
        }
        if(cmpr > 0)
        {
            lo = mid + 1;
        }
        
    }
    *found = false;
    return lo;
    
}

// Creates the set
// Initializes the SET, count, length, and data
// O(1)
SET *createSet(int maxElts)
{
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count =0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(char*) *maxElts);

    assert(sp->data!=NULL);
    return sp;
}

// Destroys set by freeing elts in data, data, then set itself
//O(n)
void destroySet(SET *sp)
{
    int i;
    assert(sp!=NULL);
    for(i=0;i<sp->count;i++)
    {
        free(sp->data[i]);
    }
    free(sp->data);
    free(sp);
}

// returns the number of elements in data
// O(1)
int numElements(SET *sp)
{
    assert(sp!=NULL);
    return sp->count;
}

// This adds the word if it is not already in the data
// it also moves the other elts over
// O(n)
void addElement(SET *sp, char *elt)
{
    bool found;
    assert(sp!=NULL);
    assert(sp->data != NULL);
    char *newelt;
    int locn = search(sp,elt,&found);
    if(found == true)
    {
        return;
    }
    assert(sp->length > sp->count);
    newelt = strdup(elt);
    assert(newelt != NULL);
    int i;
    for(i=sp->count-1;i>=locn;i--)
    {
        sp->data[i+1] = sp->data[i];
    }
    sp->data[locn] = newelt;
    sp->count++;
}

//This function removes the element at locn and 
// moves all of the other elts down to the left
//O(n)
void removeElement(SET *sp, char *elt)
{
    bool found;
    assert(sp!=NULL);
    assert(sp->data != NULL);
    int locn = search(sp, elt,&found);
    if (found == true)
    {
        free(sp->data[locn]);
        int i;
        for(i=locn+1; i<sp->count;i++)
        {
            sp->data[i-1] = sp->data[i];
        }
        sp->count--;
    }
}

// determines if specified element is in the array, 
// and if it is, it is returned
// O(logn)
char *findElement(SET *sp, char *elt)
{
    assert(sp!=NULL);
    assert(sp->data != NULL);
    bool found;


    int n = search(sp,elt,&found);
    if (found == true)
    {
        return(sp->data[n]);
    }
    return NULL;

}


// returns the words in data
// O(1)
char **getElements(SET *sp)
{
    assert(sp!=NULL);
    assert(sp->data != NULL);
    char **allElts = malloc(sizeof(char*)*sp->count);
    assert(allElts!=NULL);
    return memcpy(allElts,sp->data,sizeof(char*)*sp->count );
   
}

