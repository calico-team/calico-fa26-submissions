from bisect import bisect_right
from collections import defaultdict

def solve(N: int, K: int, L: list):
    e = defaultdict(list)
    n = defaultdict(list)
    for x, y, z, d in L:
        if d == 'E':
            e[x + y].append(x)
        else:
            n[x + y].append(x)

    cnt = 0
    for s in e:
        if s in n:
            n[s].sort()
            for x in e[s]:
                cnt += bisect_right(n[s], x + K - 1) - bisect_right(n[s], x)

    return N * K - cnt

def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append((int(X), int(Y), int(Z), D))

        print(solve(N, K, L))

if __name__ == '__main__':
    main()