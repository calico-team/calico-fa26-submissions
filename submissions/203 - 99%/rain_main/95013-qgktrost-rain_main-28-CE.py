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
    north_movers = list(north_movers), key=lambda x: x[1]
    east_movers = sorted(list(east_movers), key=lambda x: x[0])

    intersections = 0
    for drone in north_movers:
        intersections += len(east_movers)-bisect.bisect_left(east_movers, drone, key=lambda x: x[0])
    
    return (K*(len(north_movers)+len(east_movers))-intersections)


T = int(input())

for i in range(T):
    print(solve())
