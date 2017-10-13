#include <stdlib.h>
#include <stdio.h>
#include "./dyarray.h"
#include "./errcode.h"

static int test_count 	= 0;
static int test_pass 	= 0;

#define EXPECT_BASE(equal, expect, actual, format) \
	do {\
		test_count ++;\
		if(equal)\
			test_pass++;\
		else{\
			fprintf(stderr, "%s:%d:expect:" format ", actual:" format "\n", __FILE__, __LINE__, (expect), (actual));\
		}\
	}while(0)

#define EXPECT_EQUAL(expect, actual) EXPECT_BASE(((expect)==(actual)), (expect), (actual), "%d")
#define EXPECT_NULL(ptr) EXPECT_BASE(((ptr) == NULL), (void *)NULL, (ptr), "%p")

int test_dyarray(void) {
	dyArray_t * array = NULL;
	char c = 8;
	char items[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	array = DYARRAY_NEW(char, 16);
	EXPECT_EQUAL((array->size), 32);
	EXPECT_EQUAL((array->length), 0);
	EXPECT_EQUAL((array->elesize), (int)sizeof(char));

	DYARRAY_INSERT(array, items, 16, 0);
	EXPECT_EQUAL((array->size), 32);
	EXPECT_EQUAL((array->length), 16);
	EXPECT_EQUAL((array->elesize), (int)sizeof(char));
	EXPECT_EQUAL((array->arr[0]), 1);

	EXPECT_EQUAL((DYARRAY_GET(array, 0, char)), 1);
	EXPECT_EQUAL((DYARRAY_GET(array, -1, char)), 16);

	DYARRAY_DELETE(array, 0, 4);
	EXPECT_EQUAL(12, array->length);
	EXPECT_EQUAL(5, DYARRAY_GET(array, 0, char));
	EXPECT_EQUAL(6, DYARRAY_GET(array, 1, char));
	EXPECT_EQUAL(16, DYARRAY_GET(array, -1, char));

	DYARRAY_DELETE(array, 0, 12);
	EXPECT_EQUAL(0, array->length);
	DYARRAY_INSERT(array, items, 16, 0);
	EXPECT_EQUAL(16, array->length);
	DYARRAY_INSERT_SINGLE(array, &c, 10);
	EXPECT_EQUAL(8, DYARRAY_GET(array, 10, char));

	DYARRAY_DELETE_SINGLE(array, 10);
	EXPECT_EQUAL(16, DYARRAY_GET(array, -1, char));
	EXPECT_EQUAL(15, DYARRAY_GET(array, -2, char));
	EXPECT_EQUAL(14, DYARRAY_GET(array, -3, char));

	DYARRAY_FREE(array);
	EXPECT_NULL((void *)array);

	
	return 0;
}

int main() {
	test_dyarray();

	fprintf(stderr, "Tested items : %d. Passed items : %d\n", test_count, test_pass);
	return 0;
}
