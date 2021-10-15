
#include <stdio.h>

void change(int* d1, int* d2, int* d3) {
    if (*d1 && *d2 && !*d3) {
        *d1 = 0;
        *d2 = 0;
        *d3 = 1;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int d1 = 0, d2 = 0, d3 = 0;
    if (n == 1) {
        scanf("%d", &d1);
    } else if (n == 2) {
        scanf("%d", &d1);
        scanf("%d", &d2);
    } else {
        scanf("%d", &d1);
        scanf("%d", &d2);
        scanf("%d", &d3);
    }
    if (d1) {
        d2 = 1;
        d1 = 0;
    } else {
        d1 = 1;
    }
    change(&d1, &d2, &d3);
    for (int i = 3; i < n; ++i) {
        printf("%d ", d1);
        int d;
        scanf("%d", &d);
        d1 = d2;
        d2 = d3;
        d3 = d;
        change(&d1, &d2, &d3);
    }
    printf("%d ", d1);
    if (d2 && !d3) {
        printf("%d\n", d2);
    } else if (d2 || d3) {
        printf("%d ", d2);
        printf("%d\n", d3);
    }
    return 0;
}
