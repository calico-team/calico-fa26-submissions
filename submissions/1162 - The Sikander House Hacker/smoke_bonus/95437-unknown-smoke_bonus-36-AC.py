import sys
from collections import deque

def main():
    input_data = sys.stdin.buffer.read().split()
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
        recharges = deque()
        possible = True
        
        for t in A:
            while recharges and recharges[0] <= t:
                recharges.popleft()
                charges = min(2, charges + 1)
                
            if charges == 0:
                possible = False
                break
                
            charges -= 1
            
            start_time = t
            if recharges:
                start_time = max(t, recharges[-1])
            recharges.append(start_time + R)
            
        if possible:
            out.append("YES")
        else:
            out.append("NO")
            
    sys.stdout.write("\n".join(out) + "\n")

if __name__ == '__main__':
    main()