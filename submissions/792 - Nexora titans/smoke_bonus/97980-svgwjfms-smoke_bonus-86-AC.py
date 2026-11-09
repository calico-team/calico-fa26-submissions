import sys

def solve():
    data = sys.stdin.read().split()
    if not data:
        return
    
    it = iter(data)
    t = int(next(it))
    
    out = []
    for _ in range(t):
        n = int(next(it))
        r = int(next(it))
        
        c1 = 0
        c2 = 0
        possible = True
        
        for _ in range(n):
            time = int(next(it))
            if not possible:
                continue
            
            if min(c1, c2) <= time:
                if c1 <= c2:
                    c1 = max(time, c2) + r
                else:
                    c2 = max(time, c1) + r
            else:
                possible = False
        
        if possible:
            out.append("YES")
        else:
            out.append("NO")
            
    print('\n'.join(out))

if __name__ == '__main__':
    solve()