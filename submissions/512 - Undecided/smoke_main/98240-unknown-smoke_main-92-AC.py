t=int(input())
def fn():
    n,r = map(int,input().split())
    a = list(map(int,input().split()))
    ltime=0
    c=2
    for t in a:
        # Reload two
        if ltime+r+r<=t:
            c=2
        # Reload one
        elif ltime+r<=t:
            c+=1
            # Schedule second reload
            if c==1:
                ltime+=r
        c=min(2,c)
        # print(f"{t=} {c=} {ltime=}")
        if c==2: # First bomb
            ltime=t
            c-=1
        elif c==1: # Second bomb
            c-=1
        else:
            return False
    return True

for _ in range(t):
    print(("NO","YES")[fn()])