import sys

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    T = int(data[0])
    idx = 1
    
    out = []
    for _ in range(T):
        N = int(data[idx])
        R = int(data[idx+1])
        idx += 2
        
        A = [int(x) for x in data[idx:idx+N]]
        idx += N
        
      
        ready1 = 0
        ready2 = 0
        
        possible = True
        for t in A:
            
            if min(ready1, ready2) > t:
                possible = False
                break
            
           
            if ready1 <= ready2:
                
                ready1 = max(t, ready2) + R
            else:
                ready2 = max(t, ready1) + R
                
        if possible:
            out.append("YES")
        else:
            out.append("NO")
            
    print("\n".join(out))

if _name_ == '_main_':
    solve()
