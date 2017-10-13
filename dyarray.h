#ifndef __DYARRAY_H
#define __DYARRAY_H
#include <stdint.h>

typedef struct dyarray_s {
	uint32_t 	length;	//using size
	uint32_t 	size;	//capsize
	uint32_t 	elesize;//single element size
	char *		arr;	//arr ptr
} dyArray_t;

#define DYARRAY_NEW(type, length) (dyArray_new((sizeof(type)), (length)))
#define DYARRAY_GET(array, local, type)  (*((type *)dyArray_get((array), (local))))
#define DYARRAY_INSERT(array, elements, length, local) (dyArray_insert((array), (char*)(elements), (length), (local)))
#define DYARRAY_INSERT_SINGLE(array, element, local) (dyArray_insert_single(array, (char*)(element), (local)))
#define DYARRAY_DELETE(array, start, length) (dyArray_delete((array), (start), (length)))
#define DYARRAY_DELETE_SINGLE(array, local) (dyArray_delete_single(array, local))
#define DYARRAY_FREE(array)	do {dyArray_free(array); array = NULL;}while(0)


extern dyArray_t * dyArray_new(int elemsize, uint32_t length);
extern unsigned long dyArray_free(dyArray_t* array);
extern unsigned long dyArray_resize(dyArray_t* array, uint32_t length);
extern unsigned long dyArray_insert(dyArray_t* array, const char *elements, uint32_t length, int64_t local);
extern unsigned long dyArray_insert_single(dyArray_t* array, const char* element, int64_t local);
extern unsigned long dyArray_delete(dyArray_t* array, int64_t start, uint32_t length);
extern unsigned long dyArray_delete_single(dyArray_t* array, int64_t local);
extern char * dyArray_get(dyArray_t* array, int64_t local);


#endif
