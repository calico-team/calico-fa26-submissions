import sys

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    it = iter(input_data)
    t = int(next(it))
    
    out = []
    for _ in range(t):
        n = int(next(it))
        m = int(next(it))
        q = int(next(it))
        
        grid = [[0] * m for _ in range(n)]
        
        for _ in range(q):
            r_ep = int(next(it))
            c_ep = int(next(it))
            p = int(next(it))
            
            p2 = p * p
            r_min = max(0, r_ep - p)
            r_max = min(n - 1, r_ep + p)
            c_min = max(0, c_ep - p)
            c_max = min(m - 1, c_ep + p)
            
            for r in range(r_min, r_max + 1):
                dr2 = (r - r_ep) ** 2
                for c in range(c_min, c_max + 1):
                    ds = dr2 + (c - c_ep) ** 2
                    if ds <= p2:
                        grid[r][c] = p2 - ds + 1
                        
        for r in range(n):
            out.append(" ".join(map(str, grid[r])))
            
    print("\n".join(out))

if __name__ == '__main__':
    main()