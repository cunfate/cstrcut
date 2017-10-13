#ifndef __ERRORCODES_H
#define __ERRORCODES_H

typedef enum errorcodes_e {
	RET_OK = 0,
	RET_MEM_FAILED
} errorcode_t;


#define RET_ERROR(e)		do{fprintf(stderr, "Return error code %lud in func %s, %s:%d\n", e, __FUNCTION__, __FILE__, __LINE__); return (e);}while(0)

#endif
