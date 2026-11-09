import sys
from collections import deque

def solve():
   
    input = sys.stdin.read().split()
    if not input:
        return
    
    itr = iter(input)
    try:
        T = int(next(itr))
    except StopIteration:
        return
    
    for i in range(T):
        N = int(next(itr))
        R = int(next(itr))
        A = [int(next(itr)) for i in range(N)]
        
        charges = 2
        queue = deque()
        possible = True
        
        for t in A:
          
            while queue and queue[0] <= t:
                queue.popleft()
                charges += 1
            
          
            if charges > 0:
                charges -= 1
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