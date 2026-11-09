def lower_bound(arr, target):
    l, r = 0, len(arr)
    while l < r:
        m = (l + r) // 2
        if arr[m] < target:
            l = m + 1
        else:
            r = m
    return l

def upper_bound(arr, target):
    l, r = 0, len(arr)
    while l < r:
        m = (l + r) // 2
        if arr[m] <= target:
            l = m + 1
        else:
            r = m
    return l


def solve(N: int, K: int, L: list):
    answer = N*K
    east = []
    north = {}

    for x, y, z, d in L:
        if d == 'E':
            east.append((x, y))
        else:
            key = x + y
            if key not in north:
                north[key]= []
            north[key].append(x)

    for key in north:
        north[key].sort()

    for x, y in east:
        key= x + y
        if key in north:
            positions = north[key]
            left=lower_bound(positions, x)
            right=lower_bound(positions, x + K)
            answer -= right - left

    return answer

def main():
    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())

        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append((int(X), int(Y), int(Z), D))

        print(solve(N, K, L))


if __name__ == "__main__":
    main()