import sys
from collections import deque

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    T = int(input_data[0])
    idx = 1
    
    out = []
    for _ in range(T):
        N = int(input_data[idx])
        R = int(input_data[idx + 1])
        idx += 2
        
        times = []
        for _ in range(N):
            times.append(int(input_data[idx]))
            idx += 1
            
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