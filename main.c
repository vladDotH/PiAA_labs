#include "BackTracking.h"

int main() {
    DEBUG = 1;
    int n;
    scanf("%d", &n);
    Solution sln = solve(n);
    dbgPrintf("\nAnswer:\n");
    printf("%d\n", sln.size);
    for (int i = 0; i < sln.size; ++i) {
        printf("%d %d %d\n", sln.list[i].y, sln.list[i].x, sln.list[i].R);
    }
}
