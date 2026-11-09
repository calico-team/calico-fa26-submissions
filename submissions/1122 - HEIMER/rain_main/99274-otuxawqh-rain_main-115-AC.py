from bisect import bisect_left, bisect_right


def solve(N, K, L):
    east = {}
    north = {}
    for X, Y, Z, D in L:
        (east if D == 'E' else north).setdefault(X + Y, []).append(X)

    meets = 0
    for s, ns in north.items():
        es = east.get(s)
        if not es:
            continue
        es.sort()
        for x in ns:
            meets += bisect_right(es, x) - bisect_left(es, x - K + 1)

    return N * K - meets


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
