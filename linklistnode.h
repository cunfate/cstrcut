#ifndef __LINKLISTNODE_H
#define __LINKLISTNODE_H
#include <stdint.h>
#include <stdlib.h>

typedef struct linklistnode_s {
	uint32_t 	elesize;//single element size
	char *		elem;	//arr ptr

	struct linklistnode_s * next, *prev;
} linklistnode_t;


extern linklistnode_t* linklist_createNode(char* element, ssize_t elesize);
extern unsigned long linklist_insertAfter(linklistnode_t* before_node, linklistnode_t* insert_node);
extern unsigned long linklist_insertBefore(linklistnode_t* after_node, linklistnode_t* insert_node);
extern linklistnode_t* linklist_deleteAfter(linklistnode_t* before_node);
extern linklistnode_t* linklist_deleteBefore(linklistnode_t* after_node);
extern unsigned long linklist_freeNode(linklistnode_t * node);

#endif
