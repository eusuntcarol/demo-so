#include <stdio.h>
#include <stdlib.h>

int a_1;
int a_2 = 0;

int b = 1;

const int c = 2;

void print_and_wait(char *str, const void *p) {
    printf("%s:", str);
    getchar();
    printf("%p\n\n", p);
}

void f(void) {
    char *str1 = "hello there";
    print_and_wait("str1", str1);

    // ----
    // str1[1] = '.';
    // str1 = "abcd";
    // ----

    char str2[32] = "hello there";
    print_and_wait("str2", str2);

    // ----
    // str2[1] = '.';
    // str2 = "abcd";
    // ----

    int l;

    print_and_wait("l", &l);

    return;
}

int main(void) {
    int s_1;
    static int s_2;
    static int s_3 = 3;

    print_and_wait("s_1", &s_1);
    print_and_wait("s_2", &s_2);
    print_and_wait("s_3", &s_3);
    print_and_wait("a_1", &a_1);
    print_and_wait("a_2", &a_2);
    print_and_wait("b", &b);
    print_and_wait("c", &c);
    print_and_wait("f", &f);

    f();

    void *p = malloc(0x1337);

    print_and_wait("p", p);

    free(p);

    return 0;
}
