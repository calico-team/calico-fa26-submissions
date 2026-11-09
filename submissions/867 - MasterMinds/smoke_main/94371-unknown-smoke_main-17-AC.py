import sys
from collections import deque

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    itr = iter(input_data)
    T = int(next(itr))
    
    for _ in range(T):
        N = int(next(itr))
        R = int(next(itr))
        A = [int(next(itr)) for _ in range(N)]
        
        charges = 2
        queue = deque()
        possible = True
        
        for t in A:
            # Process any recharges that have finished by time t
            while queue and queue[0] <= t:
                queue.popleft()
                charges += 1
            
            # Check if a smoke charge is available
            if charges > 0:
                charges -= 1
                # Smokes recharge sequentially
                if not queue:
                    queue.append(t + R)
                else:
                    queue.append(queue[-1] + R)
            else:
                possible = False
                break
        
        if possible:
            print("YES")
        else:
            print("NO")

if __name__ == '__main__':
    solve()