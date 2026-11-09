#include <iostream>
#include <stdio.h>
using namespace std;

int prereq[10005], depth[10005], countAtDepth[10005], spaceLeft[10005],
    path[10005];
int i, j, d, e, x;
int courses, semesters, per_sem;
int deepest, answer, take, path_len, now, stop;

int main() {
  int t;
  cin >> t;
  while (t > 0) {
    t = t - 1;
    cin >> courses >> semesters >> per_sem;
    for (i = 1; i <= courses; i++) {
      scanf("%d", &prereq[i]);
    }
    if (semesters > 50001)
      semesters = 50001;

    for (i = 0; i < 10005; i++)
      depth[i] = 0;
    for (i = 0; i < 10005; i++)
      countAtDepth[i] = 0;
    for (i = 0; i < 10005; i++)
      spaceLeft[i] = 0;

    if (0) {
      int cnt = 0;
      for (i = 1; i <= courses; i++) {
        if (prereq[i] == 0)
          cnt++;
      }
      printf("%d\n", cnt);
    }

    deepest = 0;
    for (i = 1; i <= courses; i++) {
      // d = 1;
      // now = prereq[i];
      // while (now != 0) {
      //   d++;
      //   now = prereq[now];
      // }
      // depth[i] = d;

      path_len = 0;
      now = i;
      while (true) {
        if (now == 0)
          break;
        if (depth[now] != 0)
          break;
        if (path_len >= 10005)
          break;
        path[path_len] = now;
        path_len = path_len + 1;
        now = prereq[now];
      }

      if (now == 0) {
        d = 0;
      } else {
        d = depth[now];
      }

      for (j = path_len - 1; j >= 0; j--) {
        d = d + 1;
        depth[path[j]] = d;
      }

      countAtDepth[depth[i]] = countAtDepth[depth[i]] + 1;
      if (depth[i] > deepest) {
        deepest = depth[i];
      } else {
      }
    }
    // cout << "deepest " << deepest << endl;

    for (d = 1; d <= deepest; d++) {
      if (d <= semesters && d < 50001) {
        spaceLeft[d] = per_sem * (semesters - d + 1);
      } else {
        spaceLeft[d] = 0;
      }
    }

    answer = 0;
    stop = 0;
    for (d = 1; d <= deepest; d++) {
      if (stop == 0) {
        take = countAtDepth[d];
        for (e = 1; e <= d; e++) {
          if (spaceLeft[e] < take) {
            take = spaceLeft[e];
          }
          // take = smaller(take, spaceLeft[e]);
        }

        answer = answer + take;
        for (e = 1; e <= d; e++) {
          spaceLeft[e] = spaceLeft[e] - take;
        }
        // printf("depth %d took %d\n", d, take);

        if (take < countAtDepth[d]) {
          stop = 1;
        }
      }
    }
    printf("%d\n", answer);
  }
  return 0;
}
