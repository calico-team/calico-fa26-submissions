#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

int e1[200005], e2[200005], arr2[200005], flag[200005], arr[200005];
int i, j, k, x;
int n, idx, f;
long long tmp, xx;
string s;

int main() {
  cin >> s;
  cin >> n;
  if (n > 200001)
    n = 200001;


  if (s == "FIRST") {
    for (i = 1; i <= n - 1; i++) {
      scanf("%d %d", &e1[i], &e2[i]);
    }

    for (i = 0; i < 200005; i++)
      flag[i] = 0;
    for (i = 0; i < 200005; i++)
      arr2[i] = 0;
    flag[1] = 1;

    if (0) {
      for (i = 1; i <= n - 1; i++) {
        arr2[e2[i]] = e1[i];
      }
    }

    while (true) {
      f = 0;
      for (i = 1; i <= n - 1; i++) {
        if (flag[e1[i]] == 1 && flag[e2[i]] == 0) {
          arr2[e2[i]] = e1[i];
          flag[e2[i]] = 1;
          f = 1;
        } else if (flag[e2[i]] == 1 && flag[e1[i]] == 0) {
          arr2[e1[i]] = e2[i];
          flag[e1[i]] = 1;
          f = 1;
        } else {
        }
      }
      // cout << "pass done" << endl;
      if (f == 0)
        break;
    }

    tmp = 0;
    for (i = 2; i <= n; i++) {
      tmp = tmp + arr2[i];
    }
    xx = tmp % 1000000000;

    printf("%lld", xx);
    for (i = 2; i <= n; i++) {
      printf(" %d", arr2[i]);
    }
    printf("\n");
  } else {
    for (i = 1; i <= n; i++) {
      scanf("%d", &arr[i]);
    }

    idx = 0;
    for (i = 1; i <= n; i++) {
      if (arr[i] == -1) {
        idx = i;
      }
    }

    if (idx >= 2) {
      for (k = 1; k <= n; k++) {
        arr[idx] = k;
        tmp = 0;
        for (i = 2; i <= n; i++) {
          tmp = tmp + arr[i];
        }
        // printf("trying %d\n", k);
        if (tmp % 1000000000 == arr[1]) {
          k = n + 5; // found it so stop
        }
      }
    }

    for (i = 2; i <= n; i++) {
      printf("%d %d\n", i, arr[i]);
    }
  }
  return 0;
}
