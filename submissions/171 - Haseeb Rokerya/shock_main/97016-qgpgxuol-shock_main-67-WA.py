# cook your dish here
import sys
from math import isqrt

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    tokens = input_data
    
    if len(tokens) == 1 + 3 + int(tokens[2]) * 3:
        pass
    else:
        tokens = ['1'] + tokens

    iterator = iter(tokens)
    t = int(next(iterator))
    out = []
    
    for _ in range(t):
        n = int(next(iterator))
        m = int(next(iterator))
        q = int(next(iterator))
        
        grid = [[0] * m for _ in range(n)]
        
        for _ in range(q):
            rc = int(next(iterator))
            cc = int(next(iterator))
            p = int(next(iterator))
            
            p2 = p * p
            for dr in range(-p, p + 1):
                r = rc + dr
                if not (0 <= r < n):
                    continue
                
                rem = p2 - dr * dr
                if rem < 0:
                    continue
                
                dc_max = isqrt(rem)
                base = rem + 1
                row = grid[r]
                
                for dc in range(-dc_max, dc_max + 1):
                    c = cc + dc
                    if 0 <= c < m:
                        row[c] = base - dc * dc
                            
        for row in grid:
            out.append(' '.join(map(str, row)))
            
    print('\n'.join(out))

if __name__ == '__main__':
    main()