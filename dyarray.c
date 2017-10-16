#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "./dyarray.h"
#include "./errcode.h"

#define DYARRAY_MIN_NUM 	(16u)

dyArray_t * dyArray_new(int elemsize, uint32_t length) {
	dyArray_t * ret = (dyArray_t *)malloc(sizeof(dyArray_t));
	if(ret == NULL)
		return ret;

	ret->elesize 	= elemsize;
	if(length < (DYARRAY_MIN_NUM >> 1)) {
		ret->size = DYARRAY_MIN_NUM;
	} else {
		ret->size = length << 1;
	}

	ret->arr = (char*)malloc(ret->size * elemsize);
	if(ret->arr == NULL) {
		free(ret);
		return NULL;
	}

	ret->length = 0;
	return ret;
}

unsigned long dyArray_free(dyArray_t* array) {
	if(array == NULL)
		RET_ERROR((unsigned long)RET_MEM_FAILED);
	free(array->arr);
	free(array);
	return RET_OK;
}

unsigned long dyArray_resize(dyArray_t* array, uint32_t length) {
	if(array == NULL)
		RET_ERROR((unsigned long)RET_MEM_FAILED);
	int64_t i = 0;
	char *temp = NULL;
	array->size = (length)* 2;
	temp = (char*)malloc(array->size * array->elesize);
	if(temp == NULL)
		RET_ERROR((unsigned long)RET_MEM_FAILED);
	for(i = 0; i < array->length * array->elesize; i++) {
		temp[i] = array->arr[i];
	}
	free(array->arr);
	array->arr = temp;
	return RET_OK;
}

unsigned long dyArray_insert(dyArray_t* array, const char *elements, uint32_t length, int64_t local) {
	if(array == NULL || elements == NULL)
		RET_ERROR((unsigned long)RET_MEM_FAILED);
	int64_t ret = 0, i = 0;
	uint32_t local_actual;
	if(local >= 0)
		local_actual = local;
	else
		local_actual = array->length + local;
	uint32_t before_length = array->length;
	uint32_t span = length * array->elesize;
	if(before_length + length > array->size) {
		if ((ret = dyArray_resize(array, before_length + length)) != RET_OK)
			RET_ERROR((unsigned long)ret);
	}
	
	for(i = ((int64_t)(array->length) - 1) * array->elesize; i >= local_actual * array->elesize; i--) {
		array->arr[i + span] = array->arr[i];
	}

	memcpy(array->arr + (local_actual * array->elesize), elements, span);

	array->length = before_length + length;

	return RET_OK;
}

unsigned long dyArray_insert_single(dyArray_t* array, const char* element, int64_t local) {
	return dyArray_insert(array, element, 1, local);
}

unsigned long dyArray_delete(dyArray_t* array, int64_t start, uint32_t length) {
	if(array == NULL)
		RET_ERROR((unsigned long)RET_MEM_FAILED);
	if(length == 0)
		return RET_OK;
	uint32_t i = 0, span = length * array->elesize;
	uint32_t start_actual = (start >= 0) ? start : array->length + start; 
	for(i = (start_actual + length) * array->elesize; i < (array->length) * array->elesize; i++) {
		array->arr[i - span] = array->arr[i];
	}
	array->length = array->length - length;
	if(array->length < array->size / 2)
		if(dyArray_resize(array, array->length) != RET_OK)
			RET_ERROR((unsigned long)RET_MEM_FAILED);
	
	
	return RET_OK;
}

unsigned long dyArray_delete_single(dyArray_t* array, int64_t local) {
	return dyArray_delete(array, local, 1);
}

char * dyArray_get(dyArray_t* array, int64_t local) {
	if(array == NULL)
		RET_ERROR(NULL);
	if(local >= 0) {
		return (array->arr + local * array->elesize);
	} else {
		uint32_t i = array->length + local;
		return (array->arr + i * array->elesize);
	}
}
