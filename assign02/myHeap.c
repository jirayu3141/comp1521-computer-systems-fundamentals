// COMP1521 19t2 ... Assignment 2: heap management system

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myHeap.h"

/** minimum total space for heap */
#define MIN_HEAP 4096
/** minimum amount of space for a free Chunk (excludes Header) */
#define MIN_CHUNK 32


#define ALLOC 0x55555555
#define FREE  0xAAAAAAAA

/// Types:

typedef unsigned int  uint;
typedef unsigned char byte;

typedef uintptr_t     addr; // an address as a numeric type

/** The header for a chunk. */
typedef struct header {
	uint status;    /**< the chunk's status -- ALLOC or FREE */
	uint size;      /**< number of bytes, including header */
	byte data[];    /**< the chunk's data -- not interesting to us */
} header;

/** The heap's state */
struct heap {
	void  *heapMem;     /**< space allocated for Heap */
	uint   heapSize;    /**< number of bytes in heapMem */
	void **freeList;    /**< array of pointers to free chunks */
	uint   freeElems;   /**< number of elements in freeList[] */
	uint   nFree;       /**< number of free chunks */
};


/// Variables:

/** The heap proper. */
static struct heap Heap;


/// Functions:

static addr heapMaxAddr (void);
//static size_t calculateSize(addr*);
header *findSmallestFreeChunk(size_t size);
void removeFreeList(header *);
void updateFreeList(header *, size_t, size_t);
void addToFreeList(void *);
static void mergeAdjacentFree();
static void joinFreeList(addr item);
static int deleteElement(void* arr[], int n, void *x);
/** Initialise the Heap. */
int initHeap (int size)
{
	if (size < MIN_HEAP) {
		size = MIN_HEAP;
	} else if ( size % 4 != 0) {
		size = ((size / 4) + 1) * 4; // round up to the next multiplier of 4
	}

	//allocate approprite space set the header to FREE
	// + sizeof(byte[size]) because of Flexible Array Member data[]
	header *chunk = calloc(1, sizeof(byte[size]));
	if (chunk == NULL) {
		perror("failed to allocate memory");
		return -1;
	}
	chunk->status = FREE;
	chunk->size = size;
	Heap.heapMem = (addr *) chunk;
	Heap.heapSize = sizeof(byte[size]);
	//allocate freeList array so hold the chuck's position

	Heap.freeList = calloc(size/MIN_CHUNK, sizeof(addr));
	if (Heap.freeList == NULL) {
		perror("failed to allocate memory");
		return -1;
	}
	Heap.freeList[0] = (header *)Heap.heapMem;
	Heap.freeElems = size/MIN_CHUNK;
	Heap.nFree = 1;

	return 0; // this just keeps the compiler quiet
}

/** Release resources associated with the heap. */
void freeHeap (void)
{
	free (Heap.heapMem);
	free (Heap.freeList);
}

/** Allocate a chunk of memory large enough to store `size' bytes. */
void *myMalloc (int size)
{
	//if less than 1 return null
	if (size < 1)
		return NULL;
	//adjust the the nearest multiple of 4
	else if (size % 4 != 0) {
		size = ((size/4)+1) * 4;
	}
	//find the smallest free chnk larger than N + headerSize
	header *free = findSmallestFreeChunk(size);

	//if free chunk is smaller than N + HeaderSize + MIN_CHUNK, allocate the whole chunk
	if (free->size < size + sizeof(header) + MIN_CHUNK) {
		//adjust the chunk's properties
		free->status = ALLOC;		//adjust the status
		free->size = size + sizeof(header);	//adjust the size of the the chunk
		removeFreeList(free);	//update freeList
		return free->data;	//return p
	} else {	//split chunk into 2
		//adjust the chunk's properties
		free->status = ALLOC;	//adjust the status
		//keep track of original size for updating later
		size_t originalSize = free->size;
		free->size = size + sizeof(header);	//adjust the size of chunk
		updateFreeList(free, originalSize, free->size);	//update freeList with new free space
		return free->data;	//return p
	}

	return NULL; // this just keeps the compiler quiet
}

/** Deallocate a chunk of memory. */
void myFree (void *obj)
{
	//free allocated memory
	header *chunk = obj - sizeof(header);
	if ((addr) chunk > heapMaxAddr() || chunk == NULL) {
		fprintf(stderr, "Attempt to free unallocated memory\n");
		exit(1);
	}
	if( chunk->status != ALLOC){
      fprintf(stderr, "Attempt to free unallocated memory\n");
   }
	chunk->status = FREE;	// change the header status
	addToFreeList(chunk);	// add the free space to freeList

	mergeAdjacentFree();	//merge free chunks if free chunks are adjacent to each other

}


/** Return the first address beyond the range of the heap. */
static addr heapMaxAddr (void)
{
	return (addr) Heap.heapMem + Heap.heapSize;
}

/** Convert a pointer to an offset in the heap. */
int heapOffset (void *obj)
{
	addr objAddr = (addr) obj;
	addr heapMin = (addr) Heap.heapMem;
	addr heapMax =        heapMaxAddr ();
	if (obj == NULL || !(heapMin <= objAddr && objAddr < heapMax))
		return -1;
	else
		return (int) (objAddr - heapMin);
}

/** Dump the contents of the heap (for testing/debugging). */
void dumpHeap (void)
{
	int onRow = 0;

	// We iterate over the heap, chunk by chunk; we assume that the
	// first chunk is at the first location in the heap, and move along
	// by the size the chunk claims to be.
	addr curr = (addr) Heap.heapMem;
	while (curr < heapMaxAddr ()) {
		header *chunk = (header *) curr;

		char stat;
		switch (chunk->status) {
		case FREE:  stat = 'F'; break;
		case ALLOC: stat = 'A'; break;
		default:
			fprintf (
				stderr,
				"myHeap: corrupted heap: chunk status %08x\n",
				chunk->status
			);
			exit (1);
		}

		printf (
			"+%05d (%c,%5d)%c",
			heapOffset ((void *) curr),
			stat, chunk->size,
			(++onRow % 5 == 0) ? '\n' : ' '
		);

		curr += chunk->size;
	}

	if (onRow % 5 > 0)
		printf ("\n");
}

// static size_t calculateSize(addr *head) {
// 	int i = sizeof(header)+10000;
// 	for (; head[i] != 0; i++) {
// 	}
// 	return i;
// }

header *findSmallestFreeChunk(size_t size) {
	//iterate through the freeList to find the smallest available space
	header *curr;
	header * min = Heap.freeList[0];
	for (int i = 0; i < Heap.nFree; i++) {
		curr = Heap.freeList[i];
		//find the index that corresponds to the min	
		if (curr->size > size + sizeof(header)) {
			min = curr;
			break;
		}	
	}

	for (int i = 0; i < Heap.nFree; i++) {
		curr = Heap.freeList[i];
		//find the index that corresponds to the min	
		if (curr->size < min->size && curr->size > size + sizeof(header)) {
			min = curr;
		}
	}

	return min;
}

//remove the from FreeList
void removeFreeList(header *item) {
	//iterate through FreeList
	for (int i = 0; i < Heap.nFree; i++) {
		// if FreeList[i] == item, shift everything after item by 1 spot
		if (Heap.freeList[i] == item) {
			for (int j = i; j < Heap.nFree; j++) {
				Heap.freeList[j] = Heap.freeList[j+1];
			}
			break;
		}

	}
}

//update the item in the free list to point to the new free space
void updateFreeList(header *item, size_t originalSize, size_t usedSize) {
	//iterate through FreeList
	addr curr = (addr) Heap.freeList[0];
	for (int i = 0; i < Heap.nFree; i++) {
		header *chunk = (header *)curr;
		chunk = Heap.freeList[i];
		// if FreeList[i] == item, change FreeList[i] to the next available position
		if (chunk == item) {
			curr += usedSize; 
			chunk = (header *)curr;
			chunk->status = FREE;	// update status
			chunk->size = originalSize - usedSize; // update size fo the next available space
			Heap.freeList[i] = (header *)curr;	//update freeList
			break;
		
		}
		curr += chunk->size;
	}
}

void addToFreeList (void *address) {
	//loop through the freeList to see where to add
	int i;
	for (i = Heap.nFree-1; (Heap.freeList[i] > address && i >=0); i--)
		Heap.freeList[i+1] = Heap.freeList[i];
	//if the list is empty
	if (Heap.nFree == 0) {
		Heap.freeList[0] = (header *)address;
		Heap.nFree++;
	}

}

static void mergeAdjacentFree() {
	addr curr = (addr) Heap.heapMem;
	addr currNext = (addr) Heap.heapMem;
	while (curr < heapMaxAddr()) {
		header *chunk = (header *) curr;
		currNext += chunk->size;
		header *nextChunk = (header *) currNext;

		if (chunk->status == FREE && nextChunk->status == FREE) {
			//joinFreeList
			joinFreeList(curr);
			chunk->size += nextChunk->size;

		}

		curr += chunk->size;
	}

	// if they are both free, merge them
   
}

static void joinFreeList(addr item) {
	addr curr = (addr) Heap.freeList[0];
	for (int i = 0; i < Heap.nFree; i++) {
		curr = (addr) Heap.freeList[i];
		if (item == curr) {
			header *currFree = Heap.freeList[i];
			header *nextFree = Heap.freeList[i+1];
			currFree->size += nextFree->size;
			deleteElement(Heap.freeList, Heap.nFree, Heap.freeList[i+1]);
			Heap.nFree--;

		}
	}
}

// taken from GeeksforGeeks
// This function removes an element x from arr[] and 
// returns new size after removal (size is reduced only 
// when x is present in arr[] 
static int deleteElement(void* arr[], int n, void *x) 
{ 
   // Search x in array 
   int i; 
   for (i=0; i<n; i++) 
      if (arr[i] == x) 
         break; 
  
   // If x found in array 
   if (i < n) 
   { 
     // reduce size of array and move all 
     // elements on space ahead 
     n = n - 1; 
     for (int j=i; j<n; j++) 
        arr[j] = arr[j+1]; 
   } 
  
   return n; 
} 