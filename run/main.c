#include <stdio.h>

extern parser();

int main() {
    printf("Welcome to MINIREL database system\n\n");
    parser();
    printf("\n\nGoodbye from MINIREL\n");
    return 0;
}
