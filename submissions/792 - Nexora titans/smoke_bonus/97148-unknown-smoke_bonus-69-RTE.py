import sys

def solve():
    dataa = sys.stdin.read().split()
    if not dataa:
        return
    
    iteration = iter(dataa)
    tes = int(next(iteration))
    
    out = []
    for item in range(tes):
        n = int(next(iteration))
        r = int(next(iteration))
        
        c1 = 0
        c2 = 0
        possible = True
        
        for items in range(n):
            time = int(next(iteration))
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