#include <stdio.h>
#include <stddef.h>

struct A { char c; int i; };            /* char+3pad+int = 8  */
struct B { char c; double d; char c2; };/* 预期 24, padding */
struct C { int i; char c; };            /* 预期 8, 尾 padding */

int main(void) {
    printf("sizeof A=%zu  B=%zu  C=%zu\n",
           sizeof(struct A), sizeof(struct B), sizeof(struct C));
    printf("offset A.c=%zu  A.i=%zu\n",
           offsetof(struct A, c), offsetof(struct A, i));
    return 0;
}

/*
最终输出：
sizeof A=8  B=24  C=8
offset A.c=0  A.i=4 
说明A.c占用的就是4字节
*/


