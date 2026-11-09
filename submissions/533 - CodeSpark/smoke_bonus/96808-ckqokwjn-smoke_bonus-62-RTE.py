import sys
from collections import deque

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    try:
        T_str = next(iterator)
        T = int(T_str)
    except StopIteration:
        return
    
    out = []
    for _ in range(T):
        N = int(next(iterator))
        R = int(next(iterator))
        
        times = [int(next(iterator)) for _ in range(N)]
            
        charges = 2
        recharging = deque()
        possible = True
        
        for t in times:
            while recharging and recharging[0] <= t:
                recharging.popleft()
                charges += 1
            
            if charges > 2:
                charges = 2
                
            if charges > 0:
                charges -= 1
                if not recharging:
                    recharging.append(t + R)
                else:
                    recharging.append(recharging[-1] + R)
            else:
                possible = False
                break
                
        if possible:
            out.append("YES")
        else:
            out.append("NO")
            
    print("\n".join(out))

if __name__ == '__main__':
    solve()