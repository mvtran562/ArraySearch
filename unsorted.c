// Matthew Tran
// Project 2: Sets and Arrays
// COEN 12
// Week 1: Unsorted

//included libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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
// O(n)
static int search(SET *sp, char *elt)
{
    int i;
    for (i=0;i<sp->count;i++)
    {
        if (strcmp(sp->data[i],elt)==0)
            return i;
        
    }
    return -1; // returns -1 if not found
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
    return sp; //returns the set
}

// Destroys set by freeing elts in data, data, then set itself
// O(n)
void destroySet(SET *sp)
{
    
    int i;
    assert(sp!=NULL);
    for(i=0;i<sp->count;i++)
    {
        free(sp->data[i]); // frees words first
    }
    free(sp->data); // frees data next
    free(sp); // then frees the whole thing
    
}

// returns the number of elements in data
// O(1)
int numElements(SET *sp)
{
    assert(sp!=NULL);
    return sp->count;
}

// adds element to the data
// first checks if elt already exists in the data using search function
// if it does not exist, it inserts it at the next slot in the array
// increments count 
// O(n)
void addElement(SET *sp, char *elt)
{
    assert(sp!=NULL);
    assert(sp->data != NULL);
    if(search(sp,elt) != -1)
    {
        return;
    }
    assert(sp->length > sp->count);
    elt = strdup(elt);
    assert(elt != NULL);
    sp->data[sp->count] = elt;
    sp->count++;
}

// removes the specified element in data
// uses search to determine location of elt
// incrememnts count down as an element is removed
// O(n)
void removeElement(SET *sp, char *elt)
{
    
    assert(sp!=NULL);
    assert(sp->data != NULL);
    int locn = search(sp, elt);
    if (locn != -1 && sp->count >0)
    {
        free(sp->data[locn]);
        sp->count--;
        sp->data[locn] = sp->data[sp->count];
    }
    
    
}

// determines if specified element is in the array, 
// and if it is, it is returned
// O(n)
char *findElement(SET *sp, char *elt)
{
    assert(sp!=NULL);
    assert(sp->data != NULL);
    
    int n = search(sp,elt);
    if (n != -1)
    {
        return(sp->data[n]);
    }

    return NULL;

}


// returns the words in data. Returns a copy to not allow unauthorized access
// O(1)
char **getElements(SET *sp)
{
    
    assert(sp!=NULL);
    assert(sp->data != NULL);
    char **allElts = malloc(sizeof(char*)*sp->count);
    assert(allElts!=NULL);
    return memcpy(allElts,sp->data,sizeof(char*)*sp->count );
    return allElts;
    
}



