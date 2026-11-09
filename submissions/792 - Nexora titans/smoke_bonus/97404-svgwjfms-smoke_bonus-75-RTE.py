import sys

def solve():
    data = sys.stdin.read().split()
    if not data:
        return
    
    iterat = iter(data)
    tes = int(next(iterat))
    
    outer = []
    for _ in range(tes):
        n = int(next(iterat))
        r = int(next(iterat))
        
        c_1 = 0
        c_2 = 0
        possible = True
        
        for _ in range(n):
            time = int(next(iterat))
            if not possible:
                continue
            
            if min(c_1, c_2) <= time:
                if c_1 <= c_2:
                    c_1 = max(time, c_2) + r
                else:
                    c_2 = max(time, c_1) + r
            else:
                possible = False
        
        if possible:
            outer.append("YES")
        else:
            outer.append("NO")
            
    print('\n'.join(outer))

if __name__ == '__main__':
    solve()