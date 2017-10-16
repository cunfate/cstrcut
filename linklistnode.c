#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "./linklistnode.h"
#include "./errcode.h"

linklistnode_t* linklist_createNode(char* element, ssize_t elesize) {
	if(element == NULL)
		return NULL;
	linklistnode_t* node = NULL;
	node = (linklistnode_t*)malloc(sizeof(linklistnode_t));
	if(node == NULL)
		return node;
	node->elem = (char*)malloc(elesize);
	if(node->elem == NULL)
		return NULL;
	memcpy(node->elem, element, elesize);
	node->next = NULL;
	node->prev = NULL;
	return node;
}

unsigned long linklist_insertAfter(linklistnode_t* before_node, linklistnode_t* insert_node) {
	linklistnode_t* after_node = before_node->next;
	before_node->next = insert_node;
	insert_node->next = after_node;
	insert_node->prev = before_node;
	if(after_node != NULL) {
		after_node->prev = insert_node;
	}
	return RET_OK;
}

unsigned long linklist_insertBefore(linklistnode_t* after_node, linklistnode_t* insert_node) {
	linklistnode_t* before_node = after_node->prev;
	insert_node->next = after_node;
	insert_node->prev = before_node;
	after_node->prev = insert_node;
	if(before_node != NULL) {
		before_node->next = insert_node;
	}

	return RET_OK;
}

linklistnode_t* linklist_deleteAfter(linklistnode_t* before_node) {
	if(before_node == NULL || before_node->next == NULL)
		return NULL;
	linklistnode_t* delete_node = before_node->next;
	before_node->next = delete_node->next;
	if(delete_node->next != NULL)
		delete_node->next->prev = before_node;
	return delete_node;
}

linklistnode_t* linklist_deleteBefore(linklistnode_t* after_node) {
	if(after_node == NULL || after_node->prev == NULL)
		return NULL;
	linklistnode_t* delete_node = after_node->prev;
	after_node->prev = delete_node->prev;
	if(delete_node->prev != NULL) {
		delete_node->prev->next = after_node;
	}
	return delete_node;
}

unsigned long linklist_freeNode(linklistnode_t * node) {
	free(node->elem);
	free(node);
	return RET_OK;
}
