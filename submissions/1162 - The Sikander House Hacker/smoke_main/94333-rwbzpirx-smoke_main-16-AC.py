import sys
from collections import deque

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    T = int(next(iterator))
    
    out = []
    for _ in range(T):
        N = int(next(iterator))
        R = int(next(iterator))
        A = [int(next(iterator)) for _ in range(N)]
        
        charges = 2
        recharge_times = deque()
        possible = True
        
        for t in A:
            while recharge_times and recharge_times[0] <= t:
                recharge_times.popleft()
                charges = min(2, charges + 1)
            
            if charges == 0:
                possible = False
                break
            
            charges -= 1
            if not recharge_times:
                recharge_times.append(t + R)
            else:
                recharge_times.append(recharge_times[-1] + R)
                
        if possible:
            out.append("YES")
        else:
            out.append("NO")
            
    print('\n'.join(out))

if __name__ == '__main__':
    solve()