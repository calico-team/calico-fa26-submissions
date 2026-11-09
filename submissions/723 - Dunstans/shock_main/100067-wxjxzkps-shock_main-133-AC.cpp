#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

long long aa[200005], bb[200005], cc[200005];
long long temp[1000005], ans[2000005];
long long i, j, k, d, e, w, x, y, z, t, cnt, flag;
long long n, m, q, lo, hi, r1, b2;
long long tmp;
string s;


int main() {
  cin >> t;
  while (true) {
  if (t == 0)
    break;
  t--;
  cin >> n >> m >> q;
  if (q > 200001)
    q = 200001;
  for (i = 0; i <= q - 1; i++) scanf("%lld %lld %lld", &aa[i], &bb[i], &cc[i]);

  for (i = 0; i <= n * m - 1; i++) temp[i] = 0;
  for (i = 0; i <= n - 1; i++) for (j = 0; j <= m; j++) ans[i * (m + 1) + j] = j;

  if (0) {
    // old
    for (k = 0; k <= q - 1; k++) for (i = aa[k] - cc[k]; i <= aa[k] + cc[k]; i++)
        for (j = bb[k] - cc[k]; j <= bb[k] + cc[k]; j++) {
      tmp = cc[k] * cc[k] - (i - aa[k]) * (i - aa[k]) - (j - bb[k]) * (j - bb[k]) + 1;
      if (tmp > 0)
        temp[i * m + j] = tmp;
    }
  }

  for (k = q - 1; k >= 0; k--) {
    w = cc[k];
    for (d = 0; d <= cc[k]; d++) {
      // w = (int)sqrt(cc[k] * cc[k] - d * d);
      while (w * w + d * d > cc[k] * cc[k])
        w--;

      for (e = 0; e <= 1; e++) {
        if (e == 1 && d == 0)
          break;
        r1 = e == 0 ? aa[k] + d : aa[k] - d;
        lo = bb[k] - w; hi = bb[k] + w; b2 = r1 * (m + 1);

        x = lo;
        while (true) {
          if (ans[b2 + x] == x)
            break;
          x = ans[b2 + x];
        }
        y = lo;
        while (ans[b2 + y] != x) {
          z = ans[b2 + y]; ans[b2 + y] = x; y = z;
        }

        while (x <= hi) {
          temp[r1 * m + x] = cc[k] * cc[k] - d * d - (x - bb[k]) * (x - bb[k]) + 1;
          ans[b2 + x] = x + 1;
          // printf("set %lld %lld\n", r1, x);

          y = x + 1; x = x + 1;
          while (true) {
            if (ans[b2 + x] == x)
              break;
            x = ans[b2 + x];
          }
          while (ans[b2 + y] != x) {
            z = ans[b2 + y]; ans[b2 + y] = x; y = z;
          }
        }
      }
    }
  }

  for (i = 0; i <= n - 1; i++) {
    for (j = 0; j <= m - 1; j++) {
      if (j > 0)
        printf(" ");
      printf("%lld", temp[i * m + j]);
    }
    printf("\n");
  }
  }
  return 0;
}
