/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

#include <cstdio>
#include <queue>

using namespace std;

void sss() {
    int n;
    long long r;
    if (scanf("%d %lld", &n, &r) != 2) return;

    int charges = 2;
    queue<long long> q;
    bool ok = true;

    for (int i = 0; i < n; i++) {
        long long t;
        scanf("%lld", &t);

        while (!q.empty() && q.front() <= t) {
            charges++;
            q.pop();
        }

        if (charges == 0) {
            ok = false;
        }

        if (ok) {
            charges--;
            if (q.empty()) {
                q.push(t + r);
            } else {
                q.push(q.back() + r);
            }
        }
    }

    if (ok) {
        puts("YES");
    } else {
        puts("NO");
    }
}

int main() {
    int t;
    if (scanf("%d", &t) == 1) {
        while (t--) {
            sss();
        }
    }
    return 0;
}