import bisect

def solve():
    N, K = map(int, input().split())

    north_movers = set()
    east_movers = set()
    for _ in range(N):
        x, y, z, d = input().split()
        x, y, z = [int(i) for i in [x, y, z]]
        if d == 'N':
            north_movers.add((x, y))
        else:
            east_movers.add((x, y))

    north_buckets = {}
    for x, y in north_movers:
        if x+y in north_buckets:
            north_buckets[x+y].append(x)
        else:
            north_buckets[x+y] = [x]
    
    
    east_buckets = {}
    for x, y in east_movers:
        if not x+y in north_buckets:
            continue
        if x+y in east_buckets:
            east_buckets[x+y].append(x)
        else:
            east_buckets[x+y] = [x]

    for group in north_buckets:
        north_buckets[group].sort()
    for group in east_buckets:
        east_buckets[group].sort()

    intersections = 0

    for bucket in east_buckets:
        if bucket in north_buckets:
            for east in east_buckets[bucket]:
                lowest = bisect.bisect_left(north_buckets[bucket], east)
                highest = bisect.bisect_right(north_buckets[bucket], east+K-1)
                intersections += highest-lowest
    
    return (K*(len(north_movers)+len(east_movers))-intersections)


T = int(input())
for i in range(T):
    print(solve())
