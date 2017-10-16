#include "./errcode.h"
#include "./linklist.h"
#include "./linklistnode.h"
#include <stdio.h>

linklist_t* linklist_create() {
	linklist_t* list = (linklist_t*)malloc(sizeof(linklist_t));
	if(list == NULL)
		return NULL;
	list->length = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

unsigned long linklist_insert_single(linklist_t* list, char* elements, ssize_t elesize, int64_t local) {
	if(elements == NULL || list == NULL || local > list->length)
		RET_ERROR((unsigned long)RET_MEM_FAILED);
	uint32_t i = 0, local_actual = 0;
	linklistnode_t *now = list->head;
	local_actual = (local >= 0)?local:(local+list->length);
	for(i = 0; i < local_actual; i++) {
		now = now->next;
	}
	linklistnode_t* insert_node = linklist_createNode(elements, elesize);
	return linklist_insertAfter(now, insert_node);
}

unsigned long linklist_insert(linklist_t* list, char* elements, ssize_t elesize, int64_t local, ssize_t length) {
	if(list == NULL || elements == NULL || local > list->length)
		RET_ERROR((unsigned long)RET_MEM_FAILED);
	ssize_t i = 0;
	for(i = 0; i < length; i++) {
		if(linklist_insert_single(list, elements, elesize, local))
			return (unsigned long)RET_MEM_FAILED;
		elements += elesize;
		local ++;
	}
	return RET_OK;
}

linklistnode_t* linklist_delete_single(linklist_t* list, int64_t local) {
	if(list == NULL || local > list->length)
		return NULL;
	uint32_t i = 0;
	uint32_t local_actual = (local >= 0) ? (local) : (local + list->length);
	linklistnode_t* now = list->head;
	for(i = 0; i < local_actual; i++) {
		now = now->next;
	}
	return linklist_deleteAfter(now);
}

linklistnode_t* linklist_delete(linklist_t* list, int64_t local, uint32_t length) {
	if(list == NULL || local > list->length || local + length > list->length)
		return NULL;
	uint32_t i = 0;
	linklistnode_t* now;
	for(i = 0; i < length; i++) {
		if((now = linklist_delete_single(list, local)) == NULL)
			return NULL;
	}
	return now;
}
