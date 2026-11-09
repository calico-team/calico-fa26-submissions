t = int(input())
for _ in range(t):
    n, r = map(int, input().split())
    a = list(map(int, input().split()))
    
    ch = 2
    nxt = 0
    ok = True
    
    for tm in a:
        while ch < 2 and nxt <= tm:
            ch += 1
            if ch < 2:
                nxt += r
                
        if ch == 0:
            ok = False
            break
        
        if ch == 2:
            nxt = tm + r
            
        ch -= 1
        
    print("YES" if ok else "NO")