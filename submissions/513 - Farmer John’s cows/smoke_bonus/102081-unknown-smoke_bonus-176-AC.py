t = int(input())

for i in range(t):
    n, r = map(int, input().split())
    a = list(map(int, input().split()))
    charges = 2
    ready = []
    ok = True 
    for k in range(n):
        now = a[k]    
        while len(ready) > 0:
            if ready[0] <= now:
                ready.pop(0)
                charges = charges + 1
            else:
                break              
        if charges == 0:
            ok = False
            break           
        if charges == 2:
            ready.append(now + r)
        elif charges == 1:
            ready.append(ready[0] + r)   
        charges = charges - 1
        
    if ok:
        print("YES")
    else:
        print("NO")
