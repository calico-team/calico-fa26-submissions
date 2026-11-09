import sys


def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    N = int(data[0])
    K = int(data[1])

    drones = []
    idx = 2
    for _ in range(N):
        x = int(data[idx])
        y = int(data[idx + 1])
        z = int(data[idx + 2])
        d = data[idx + 3]
        drones.append((x, y, z, d))
        idx += 4

    blocked_intervals = [[] for _ in range(N)]

    for i in range(N):
        xi, yi, zi, di = drones[i]
        for j in range(N):
            if i == j:
                continue
            xj, yj, zj, dj = drones[j]

            if zj <= zi:
                continue

            if di == dj:
                if xi == xj and yi == yj:
                    blocked_intervals[i].append((0, K - 1))
            else:
                if di == 'E' and dj == 'N':
                    t1 = xj - xi
                    t2 = yi - yj
                    if t1 == t2 and 0 <= t1 < K:
                        blocked_intervals[i].append((t1, t1))
                elif di == 'N' and dj == 'E':
                    t1 = xi - xj
                    t2 = yj - yi
                    if t1 == t2 and 0 <= t1 < K:
                        blocked_intervals[i].append((t1, t1))

    total_rain = 0

    for i in range(N):
        intervals = blocked_intervals[i]
        if not intervals:
            total_rain += K
            continue

        intervals.sort()
        merged = []
        curr_start, curr_end = intervals[0]

        for start, end in intervals[1:]:
            if start <= curr_end + 1:
                curr_end = max(curr_end, end)
            else:
                merged.append((curr_start, curr_end))
                curr_start, curr_end = start, end
        merged.append((curr_start, curr_end))

        blocked_nights = 0
        for start, end in merged:
            blocked_nights += (end - start + 1)

        total_rain += (K - blocked_nights)

    print(total_rain)


if __name__ == '__main__':
    solve()
