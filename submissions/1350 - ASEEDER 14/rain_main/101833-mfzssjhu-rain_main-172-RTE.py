import sys

def solve(N: int, K: int, L: list):
    events = {}
    
    for i in range(N):
        x, y, z, d = L[i]
        if d == 'E':
            dx, dy = 1, 0
        else:
            dx, dy = 0, 1
            
        for t in range(K):
            nx = x + dx * t
            ny = y + dy * t
            
            key = (t, nx, ny)
            if key not in events:
                events[key] = []
            events[key].append(z)
            
    blocked_count = 0
    for key, z_list in events.items():
        if len(z_list) > 1:
            z_list.sort(reverse=True)
            max_z = z_list[0]
            for z in z_list[1:]:
                if z < max_z:
                    blocked_count += 1
                    
    return K * N - blocked_count

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
