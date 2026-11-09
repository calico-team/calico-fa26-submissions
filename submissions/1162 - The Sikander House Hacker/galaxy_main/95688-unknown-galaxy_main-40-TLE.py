import sys
from collections import deque

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    iterator = iter(input_data)
    T = int(next(iterator))
    for _ in range(T):
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))
        grid = [next(iterator) for _ in range(N)]
        queries = []
        for _ in range(Q):
            r_s = int(next(iterator))
            c_s = int(next(iterator))
            r_e = int(next(iterator))
            c_e = int(next(iterator))
            queries.append((r_s, c_s, r_e, c_e))
        
        for r_s, c_s, r_e, c_e in queries:
            queue = deque([(r_s, c_s, 0)])
            visited = set([(r_s, c_s, 0)])
            found = False
            while queue:
                r, c, m = queue.popleft()
                if r == r_e and c == c_e:
                    found = True
                    break
                for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < N and 0 <= nc < M:
                        tile = grid[nr][nc]
                        active = (tile == '.') or (tile == 'B' and m == 0) or (tile == 'R' and m == 1)
                        if active and (nr, nc, m) not in visited:
                            visited.add((nr, nc, m))
                            queue.append((nr, nc, m))
                if grid[r][c] == '.':
                    nm = 1 - m
                    if (r, c, nm) not in visited:
                        visited.add((r, c, nm))
                        queue.append((r, c, nm))
            if found:
                print("YES")
            else:
                print("NO")

if __name__ == '__main__':
    main()