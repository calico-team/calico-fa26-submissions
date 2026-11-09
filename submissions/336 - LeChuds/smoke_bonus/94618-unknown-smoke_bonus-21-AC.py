from collections import deque

def solve():
    n, r = map(int, input().split())
    a = list(map(int, input().split()))
    
    recharges = deque()
    possible = True
    
    for time in a:
        while recharges and recharges[0] <= time:
            recharges.popleft()
            
        if len(recharges) == 2:
            possible = False
            break
            
        start_time = time
        if recharges:
            start_time = max(start_time, recharges[-1])
        recharges.append(start_time + r)
        
    if possible:
        print("YES")
    else:
        print("NO")

t = int(input())
for i in range(t):
    solve()