
from collections import defaultdict
def solve_case(N, K):
    groups = defaultdict(lambda: [[], []])
    for _ in range(N):
        x, y, z, d = input().split()
        x = int(x)
        y = int(y)
        key = x + y
        if d == "E":
            groups[key][0].append(x)
        else:
            groups[key][1].append(x)
    total_water = N * K
    blocked = 0
    for east, north in groups.values():

        if not east or not north:
            continue
        east.sort()
        north.sort()
        left = 0
        right = 0
        m = len(north)

        for x in east:
            while left < m and north[left] < x:
                left += 1
            if right < left:
                right = left
            while right < m and north[right] < x + K:
                right += 1
            blocked += right - left
    return total_water - blocked
def main():

    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())
        answer = solve_case(N, K)
        print(answer)

if __name__ == "__main__":
    main()
