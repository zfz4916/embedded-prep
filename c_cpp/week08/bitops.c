#include <stdio.h>
#include <stdint.h>

void set_bit   (uint32_t *reg, int n) {
    *reg |= (1u << n);
}

void clear_bit (uint32_t *reg, int n) {
    *reg &= ~(1u << n);
}

void toggle_bit(uint32_t *reg, int n) {
    *reg ^= (1u << n);
}

int read_bit(uint32_t reg, int n) {
    return (reg >> n) & 1u;
}


struct Counter {
    int x;
    int y;
};

void swap_wrong(int a, int b) {
    printf("swap_wrong: a = %d, b = %d\n", a, b);
    printf("swap_wrong: &a = %p, &b = %p\n", (void *)&a, (void *)&b);
    int tmp = a;
    a = b;
    b = tmp;
    printf("swap_wrong: a = %d, b = %d\n", a, b);
}
void swap_ok (int *a, int *b) {
    printf("swap_ok: *a = %d, *b = %d\n", *a, *b);
    printf("swap_ok: a = %p, b = %p\n", (void *)a, (void *)b);
    printf("swap_ok: &a = %p, &b = %p\n", (void *)&a, (void *)&b);
    int tmp = *a;
    *a = *b;
    *b = tmp;
    printf("swap_ok: a = %d, b = %d\n", *a, *b);
}
void inc_by_ptr(struct Counter *c) {
    printf("inc_by_ptr: c->x = %d, c->y = %d\n", c->x, c->y);
    printf("inc_by_ptr: &(c->x) = %p, &(c->y) = %p\n", (void *)&(c->x), (void *)&(c->y));
    c->x++;
    c->y++;
    printf("inc_by_ptr: c->x = %d, c->y = %d\n", c->x, c->y);
}

int main (void) {
    uint32_t x = 0;
    set_bit(&x, 31);
    printf("x = %u\n", x);
    clear_bit(&x, 31);
    printf("x = %u\n", x);
    toggle_bit(&x, 31);
    printf("x = %u\n", x);
    toggle_bit(&x, 31);
    printf("x = %u\n", x);
    printf("read_bit(x, 31) = %u\n", read_bit(x, 31));
    printf("read_bit(x, 0) = %u\n", read_bit(x, 0));
    printf("read_bit(0xA5, 0) = %u\n", read_bit(0xA5, 0)); 
    printf("read_bit(0xA5, 5) = %u\n", read_bit(0xA5, 5)); 

    int a = 10;
    int b = 20;
    printf("main:&a = %p, &b = %p\n", (void *)&a, (void *)&b);
    swap_wrong(a, b);
    printf("main: a = %d, b = %d\n", a, b);
    swap_ok(&a, &b);
    printf("main: a = %d, b = %d\n", a, b);
    struct Counter c = {10, 20};
    printf("main: c.x = %d, c.y = %d\n", c.x, c.y);
    printf("main: &(c.x) = %p, &(c.y) = %p\n", (void *)&(c.x), (void *)&(c.y));
    inc_by_ptr(&c);
    printf("main: c.x = %d, c.y = %d\n", c.x, c.y);
    return 0;
}
