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
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    T = int(next(iterator))
    
    for _ in range(T):
        N = int(next(iterator))
        K = int(next(iterator))
        L = []
        for _ in range(N):
            x = int(next(iterator))
            y = int(next(iterator))
            z = int(next(iterator))
            d = next(iterator)
            L.append((x, y, z, d))
        print(solve(N, K, L))

if __name__ == '__main__':
    main()
