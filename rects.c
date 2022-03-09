#include "BackTracking.h"

int main() {
    DEBUG = 1;
    int n, m;
    scanf("%d %d", &n, &m);
    int c;
    Solution sln = advancedSolve(n, m, &c);
    printf("\nAnswer\nSize: %d\n", sln.size);
    for (int i = 0; i < sln.size; ++i) {
        printf("%d %d %d\n", sln.list[i].y, sln.list[i].x, sln.list[i].R);
    }
    printf("Count: %d", c);
}
