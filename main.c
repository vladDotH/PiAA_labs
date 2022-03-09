#include "BackTracking.h"

int main() {
    int n;
    scanf("%d", &n);
    Solution sln = solve(n);
    printf("%d\n", sln.size);
    for (int i = 0; i < sln.size; ++i) {
        printf("%d %d %d\n", sln.list[i].y, sln.list[i].x, sln.list[i].R);
    }
}