# a basic structure based on C
---
## 1. dynamic array
just include `errorcode.h` and `dyarray.h`

There are some examples:

Create dynamic array:
`dyArray_t array = DYARRAY_NEW(char, 16);`


Insert elements:
`char items[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};`
`DYARRAY_INSERT(array, items, 16);`
`DYARRAY_INSERT_SINGLE(array, items + 1, 10);`


Get elements:
`DYARRAY_GET(array, 0, char);`


Delete elements:
`DYARRAY_DELETE(array, 0, 4);`
`DYARRAY_DELETE_SINGLE(array, 10);`


Free array:
`DYARRAY_FREE(array);`
