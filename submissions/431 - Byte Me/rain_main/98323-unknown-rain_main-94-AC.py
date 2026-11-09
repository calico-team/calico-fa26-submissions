def solve(N, K):
    groups = {}
    seen = set()

    for i in range(N):
        x, y, z, d = input().split()
        x = int(x)
        y = int(y)

        if (x, y, d) in seen:
            continue

        seen.add((x, y, d))
        s = x + y

        if s not in groups:
            groups[s] = [[], []]

        if d == "E":
            groups[s][0].append(x)
        else:
            groups[s][1].append(x)

    total = len(seen) * K

    for east, north in groups.values():
        east.sort()
        north.sort()
        left = 0
        right = 0

        for x in east:
            while left < len(north) and north[left] < x:
                left += 1
            while right < len(north) and north[right] < x + K:
                right += 1
            total -= right - left

    return total


T = int(input())

for _ in range(T):
    N, K = map(int, input().split())
    print(solve(N, K))