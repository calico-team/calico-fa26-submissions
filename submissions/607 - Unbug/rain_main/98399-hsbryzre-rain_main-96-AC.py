def solve(N, K, L):
    east = {}
    north = {}
    for X, Y, Z, D in L:
        key = X + Y
        if D == 'E':
            east[key] = east.get(key, []) + [X]
        else:
            north[key] = north.get(key, []) + [X]

    meetings = 0
    for key in north:
        for nx in north.get(key, []):
            for ex in east.get(key, []):
                if 0 <= nx - ex <= K - 1:
                    meetings += 1

    return N * K - meetings


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