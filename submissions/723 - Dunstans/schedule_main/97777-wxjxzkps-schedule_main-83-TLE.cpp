#include <iostream>
#include <stdio.h>
using namespace std;

int prereq[10005], chainBelow[10005], taken[10005], canTake[10005];
int i, j, k;
int courses, semesters, per_sem;
int temp, answer;

int main() {
  int t;
  cin >> t;
  while (t > 0) {
    t = t - 1;
    cin >> courses >> semesters >> per_sem;
    for (i = 1; i <= courses; i++) {
      cin >> prereq[i];
    }

    for (i = 1; i <= courses; i++)
      chainBelow[i] = 1;
    for (i = 1; i <= courses; i++)
      taken[i] = 0;
    for (i = 1; i <= courses; i++)
      canTake[i] = 0;

    for (i = 1; i <= courses; i++) {
      temp = 1;
      j = prereq[i];
      while (true) {
        if (j == 0)
          break;
        temp = temp + 1;
        if (chainBelow[j] < temp) {
          chainBelow[j] = temp;
        } else {
        }
        j = prereq[j];
      }
    }

    answer = 0;
    for (int sem = 1; sem <= semesters; sem++) {
      for (i = 1; i <= courses; i++) {
        if (taken[i] == 1) {
          canTake[i] = 0;
        } else if (prereq[i] == 0) {
          canTake[i] = 1;
        } else if (taken[prereq[i]] == 1) {
          canTake[i] = 1;
        } else {
          canTake[i] = 0;
        }
      }

      int picked = 0;
      while (picked < per_sem) {
        int best = -1;
        int bestChain = -1;
        for (i = 1; i <= courses; i++) {
          if (canTake[i] == 1 && chainBelow[i] > bestChain) {
            best = i;
            bestChain = chainBelow[i];
          }
        }
        if (best == -1) {
          picked = per_sem;
        } else {
          canTake[best] = 0;
          taken[best] = 1;
          answer = answer + 1;
          picked = picked + 1;
        }
      }
    }
    printf("%d\n", answer);
  }
  return 0;
}
