#include <stdio.h>
#include <stdlib.h>

int global_uninit;             // BSS
int global_init = 1;           // .data
const char* msg = "hello";     // .rodata（指针在 .data，字符串在 .rodata）

int main() {
    int local;                 // stack
    int* heap = malloc(sizeof(int));  // heap
    printf("代码段(.text)   : main=%p\n", (void*)main); 
    //the name of the function is pointer
    printf("常量(.rodata)   : msg =%p\n", (void*)msg);  //pointer
    printf("已初始化(.data) : g_init =%p\n", (void*)&global_init);  //variable
    printf("未初始化(BSS)   : g_uninit=%p\n", (void*)&global_uninit); //variable
    printf("局部变量(stack)  : local  =%p\n", (void*)&local);   //variable
    printf("堆变量(heap)    : heap   =%p\n", (void*)heap);  //pointer
    /* 
    The `%p` format specifier （格式化符） only expects a `void*` argument. 
    Passing an `int*`, `char*`, or even a function pointer is strictly undefined behavior (UB). 
    */
    free(heap);

    return 0;
}
