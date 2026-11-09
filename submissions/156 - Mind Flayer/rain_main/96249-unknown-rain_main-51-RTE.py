from bisect import bisect_left, bisect_right

def solve(N: int, K: int, L: list):
    groups = {}
    for X, Y, Z, D in L:
        s = X + Y
        if s not in groups:
            groups[s] = ([], [])
        if D == 'E':
            groups[s][0].append(X)
        else:
            groups[s][1].append(X)
    meet = 0
    for es, ns in groups.values():
        if not es or not ns:
            continue
        ns.sort()
        for x in es:
            meet += bisect_right(ns, x + K - 1) - bisect_left(ns, x)
    return N * K - meet

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