def solve(N, M, Q, earthquakes):
    grid = [[0] * M for _ in range(N)]
    
    for X, Y, P in earthquakes:
        r_epicenter = Y  
        c_epicenter = X  
        p2 = P * P
        
        row_min = max(0, r_epicenter - P)
        row_max = min(N - 1, r_epicenter + P)
        col_min = max(0, c_epicenter - P)
        col_max = min(M - 1, c_epicenter + P)
        
        for r in range(row_min, row_max + 1):
            dr2 = (r - r_epicenter) ** 2
            for c in range(col_min, col_max + 1):
                ds = dr2 + (c - c_epicenter) ** 2
                if ds <= p2:
                    grid[r][c] = p2 - ds + 1
                    
    return grid


def main():
    import sys
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    it = iter(input_data)
    T = int(next(it))
    for _ in range(T):
        N, M, Q = int(next(it)), int(next(it)), int(next(it))
        earthquakes = []
        for _ in range(Q):
            X, Y, P = int(next(it)), int(next(it)), int(next(it))
            earthquakes.append((X, Y, P))
        answer = solve(N, M, Q, earthquakes)
        for row in answer:
            print(' '.join(map(str, row)))

if __name__ == '__main__':
    main()
```[cite: 2, 3, 4, 5]
