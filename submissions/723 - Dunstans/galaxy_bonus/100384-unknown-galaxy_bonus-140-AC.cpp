#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

char str[205][205];
int temp[400005], vis[400005];
int ox[4] = {1, -1, 0, 0};
int oy[4] = {0, 0, 1, -1};
int i, j, k, w, z, t, cnt, flag;
int n, m, q, a1, a2, a3, a4, st, en, head, tail, cur, nxt, md, cell, ni, nj, c1;
char ch;
string s;

int main() {
  cin >> t;
  while (true) {
    if (t == 0)
      break;
    t--;
    cin >> n >> m >> q;
    for (i = 0; i < n; i++)
      scanf("%s", str[i]);

    for (i = 0; i <= 400004; i++)
      temp[i] = 0;

    // dont touch
    c1 = 0;
    for (k = 0; k < n * m * 2; k++) {
      if (temp[k] != 0)
        continue;
      md = k % 2;
      cell = k / 2;
      i = cell / m;
      j = cell % m;
      ch = str[i][j];
      if (ch == 'B' && md == 1)
        continue;
      if (ch == 'R' && md == 0)
        continue;

      c1++;
      head = 0;
      tail = 0;
      temp[k] = c1;
      vis[tail] = k;
      tail++;
      while (head < tail) {
        cur = vis[head];
        head++;
        md = cur % 2;
        cell = cur / 2;
        i = cell / m;
        j = cell % m;
        if (str[i][j] == '.') {
          nxt = cell * 2 + 1 - md;
          if (temp[nxt] == 0) {
            temp[nxt] = c1;
            vis[tail] = nxt;
            tail++;
          } else {
          }
        }
        for (w = 0; w < 4; w++) {
          ni = i + ox[w];
          nj = j + oy[w];
          if (ni < 0 || ni >= n || nj < 0 || nj >= m)
            continue;
          ch = str[ni][nj];
          if (ch == 'B' && md == 1)
            continue;
          if (ch == 'R' && md == 0)
            continue;
          nxt = (ni * m + nj) * 2 + md;
          if (temp[nxt] == 0) {
            temp[nxt] = c1;
            vis[tail] = nxt;
            tail++;
          }
        }
      }
      // printf("group %d size %d\n", c1, tail);
    }

    for (z = 0; z < q; z++) {
      scanf("%d %d %d %d", &a1, &a2, &a3, &a4);

      if (0) {
        if (str[a3][a4] == '.')
          printf("YES\n");
      }

      st = (a1 * m + a2) * 2;
      en = (a3 * m + a4) * 2;
      flag = 0;
      if (temp[en] != 0 && temp[en] == temp[st])
        flag = 1;
      if (temp[en + 1] != 0 && temp[en + 1] == temp[st])
        flag = 1;
      if (flag == 1)
        printf("YES\n");
      else
        printf("NO\n");
    }
  }
  return 0;
}
