/* 大小端验证 */
#include <stdio.h>
union E { int i; unsigned char b[4]; };

int main(void) {
    union E u; 
    u.i = 0x12345678;   //这里写到了addr中，再使用b的时候就可以直接读取每个字节分别写进去了什么数据
    printf("b[0..3]= %02x %02x %02x %02x  ->  %s\n",
        u.b[0], u.b[1], u.b[2], u.b[3],
        u.b[0]==0x78 ? "little-endian (x86/ARM)" : "big-endian");
    return 0;
}

/*
最后结果：b[0..3]= 78 56 34 12  ->  little-endian (x86/ARM)
因此是小端 低位数据78被放在了低位地址u.b[0]
*/