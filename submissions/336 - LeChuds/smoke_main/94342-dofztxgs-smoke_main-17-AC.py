def solve():
    n, r = map(int, input().split())
    a = list(map(int, input().split()))
    
    recharges = []
    possible = True
    
    for time in a:
        new_recharges = []
        for t_rec in recharges:
            if t_rec > time:
                new_recharges.append(t_rec)
        recharges = new_recharges
        
        if len(recharges) >= 2:
            possible = False
            break
            
        start_time = time
        if len(recharges) > 0:
            start_time = max(start_time, recharges[-1])
        recharges.append(start_time + r)
        
    if possible:
        print("YES")
    else:
        print("NO")

t = int(input())
for i in range(t):
    solve()
