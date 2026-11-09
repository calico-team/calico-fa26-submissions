#include <algorithm>
#include <cstdio>
using namespace std;
#define ll long long

int x[100005], y[100005], z[100005];
char dir[100005];
ll northList[100005];

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int drones;
    ll nights;
    scanf("%d %lld", &drones, &nights);
    for (int i = 0; i < drones; i++) {
      scanf("%d %d %d %c", &x[i], &y[i], &z[i], &dir[i]);
    }

    ll answer = drones * nights;

    int northCount = 0;
    for (int i = 0; i < drones; i++) {
      if (dir[i] == 'N') {
        ll diag = x[i] + y[i];
        northList[northCount] = diag * 1000000 + x[i];
        northCount++;
      }
    }
    sort(northList, northList + northCount);

    for (int i = 0; i < drones; i++) {
      if (dir[i] != 'E')
        continue;

      ll diag = x[i] + y[i];
      ll farX = x[i] + nights - 1;
      if (farX > 100000)
        farX = 100000;

      ll lo = diag * 1000000 + x[i];
      ll hi = diag * 1000000 + farX;

      int meet = upper_bound(northList, northList + northCount, hi) -
                 upper_bound(northList, northList + northCount, lo);
      answer -= meet;
    }

    printf("%lld\n", answer);
  }
  return 0;
}
