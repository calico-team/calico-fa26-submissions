#include <iostream>
#include <stdio.h>
using namespace std;

char str[205][205];
int temp[400005], vis[400005];
int ox[3] = {1, -1, 0}, oy[3] = {0, 0, 1};
int t, n, m, q, a, b, c, d, i, j, h, e, x, y, w;

int main() {
  cin >> t;
  while (t--) {
    cin >> n >> m >> q;
    for (i = 0; i < n; i++)
      scanf("%s", str[i]);
    while (q--) {
      scanf("%d %d %d %d", &a, &b, &c, &d);
      for (i = 0; i <= 400004; i++)
        temp[i] = 0;
      h = 0;
      e = 0;
      y = a * m;
      y = y + b;
      y = y * 2;
      temp[y] = 1;
      vis[e] = y;
      e++;
      while (h < e) {
        x = vis[h];
        h++;
        i = x / 2;
        i = i / m;
        j = x / 2;
        j = j % m;
        if (str[i][j] == '.') {
          y = x / 2;
          y = y * 2;
          y = y + 1;
          y = y - x % 2;
          if (temp[y] == 0) {
            temp[y] = 1;
            vis[e] = y;
            e++;
          }
        }
        for (w = 0; w < 3; w++) {
          if (i + ox[w] < 0)
            continue;
          if (i + ox[w] >= n)
            continue;
          if (j + oy[w] >= m)
            continue;
          if (str[i + ox[w]][j + oy[w]] == 'B') {
            if (x % 2 == 1) {
              continue;
            }
          }
          if (str[i + ox[w]][j + oy[w]] == 'R') {
            if (x % 2 == 0) {
              continue;
            }
          }
          y = i + ox[w];
          y = y * m;
          y = y + j;
          y = y + oy[w];
          y = y * 2;
          y = y + x % 2;
          if (temp[y] == 0) {
            temp[y] = 1;
            vis[e] = y;
            e++;
          }
        }
      }
      // printf("reached %d\n",e);

      y = c * m;
      y = y + d;
      y = y * 2;
      if (temp[y] == 1)
        printf("YES\n");
      else
        printf("NO\n");
    }
  }
  return 0;
}
