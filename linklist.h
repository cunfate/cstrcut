#ifndef __LINKLIST_H
#define __LINKLIST_H

#include "./linklistnode.h"

typedef struct linklist_s {
	ssize_t length;
	linklistnode_t *head, *tail;
}linklist_t;
#endif
