import sys

def solve(N: int, K: int, L: list):
    east_drones = []
    north_drones = []
    
    for i, (x, y, z, d) in enumerate(L):
        if d == 'E':
            east_drones.append((x, y, z, i))
        else:
            north_drones.append((x, y, z, i))
            
    blocked_nights = [bytearray(K) for _ in range(N)]
    
    for x1, y1, z1, idx1 in east_drones:
        for x2, y2, z2, idx2 in north_drones:
            t = y1 - y2
            if 0 <= t < K:
                if x2 + t == x1:
                    if z1 < z2:
                        blocked_nights[idx1][t] = 1
                    elif z2 < z1:
                        blocked_nights[idx2][t] = 1

    for i in range(len(east_drones)):
        for j in range(i + 1, len(east_drones)):
            x1, y1, z1, idx1 = east_drones[i]
            x2, y2, z2, idx2 = east_drones[j]
            if y1 == y2:
                dist = abs(x1 - x2)
                if dist < K:
                    for t in range(dist, K):
                        if z1 < z2:
                            blocked_nights[idx1][t] = 1
                        elif z2 < z1:
                            blocked_nights[idx2][t] = 1

    for i in range(len(north_drones)):
        for j in range(i + 1, len(north_drones)):
            x1, y1, z1, idx1 = north_drones[i]
            x2, y2, z2, idx2 = north_drones[j]
            if x1 == x2:
                dist = abs(y1 - y2)
                if dist < K:
                    for t in range(dist, K):
                        if z1 < z2:
                            blocked_nights[idx1][t] = 1
                        elif z2 < z1:
                            blocked_nights[idx2][t] = 1

    total_blocked = 0
    for i in range(N):
        total_blocked += sum(blocked_nights[i])
        
    return K * N - total_blocked

def main():
    try:
        T = int(sys.stdin.readline())
    except (IOError, ValueError):
        return
        
    for _ in range(T):
        line = sys.stdin.readline()
        if not line:
            break
        N, K = map(int, line.split())
        L = []
        for _ in range(N):
            x, y, z, d = sys.stdin.readline().split()
            L.append((int(x), int(y), int(z), d))
        print(solve(N, K, L))

if __name__ == '__main__':
    main()
