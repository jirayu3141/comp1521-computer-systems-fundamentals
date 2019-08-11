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
static size_t calculateSize(header*);

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

	addr p; 	//pointer to points to available data
	header *curr; 
	//locate the available space
	for (int i = 0; i < Heap.nFree; i++) {
		curr = Heap.freeList[i];
		//if found an appropriate location
		if (curr->size > (size + sizeof(header) + MIN_CHUNK)) {
			p = (addr)curr->data;	//points to the data section
			//adjust properties
			curr->status = ALLOC;
			curr->size = size + sizeof(header);
			//indicate the properties of the next free chunk
			Heap.freeList[i] += (size + sizeof(header));
			curr = Heap.freeList[i];
			curr->status = FREE;
			curr->size = calculateSize(curr);
			break;

		} else if (curr->size <= (size + sizeof(header)) && curr->size > size) {
			p = (addr)curr->data;
			curr->size = size+sizeof(header);
			curr->status = ALLOC;
		}
	}
	




	return (void *)p; // this just keeps the compiler quiet
}

/** Deallocate a chunk of memory. */
void myFree (void *obj)
{
	/// TODO ///
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

static size_t calculateSize(header *head) {
	return 0;
}