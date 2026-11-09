#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

long long aa[200005], bb[200005], cc[200005];
long long vis[1000005];
long long i, j, k, t, tmp, x, cnt, flag;
long long n, m, q;
string s;

int main() {
  cin >> t;
  while (true) {
  if (t == 0)
    break;
  t--;
  cin >> n >> m >> q;
  for (i = 0; i <= q - 1; i++) scanf("%lld %lld %lld", &aa[i], &bb[i], &cc[i]);

  for (i = 0; i <= 1000004; i++) vis[i] = 0;

  if (0) {
    // tried going backwards, didnt work
    for (k = q - 1; k >= 0; k--) {
      for (i = 0; i <= n * m - 1; i++) {
        if (vis[i] == 0)
          cnt++;
      }
    }
  }

  // every earthquake, every block
  for (k = 0; k <= q - 1; k++) {
    for (i = 0; i <= n - 1; i++) {
      for (j = 0; j <= m - 1; j++) {
        tmp = cc[k] * cc[k] - ((i - aa[k]) * (i - aa[k]) + (j - bb[k]) * (j - bb[k])) + 1;
        // printf("%lld %lld %lld\n", i, j, tmp);
        if (tmp <= 0)
          continue;
        vis[i * m + j] = tmp;
      }
    }
  }

  for (i = 0; i <= n - 1; i++) {
    for (j = 0; j <= m - 1; j++) {
      if (j > 0)
        printf(" ");
      printf("%lld", vis[i * m + j]);
    }
    puts("");
  }
  }
  return 0;
}
