from collections import deque
for i in range(int(input())):
    times,interval=map(int,input().split())
    smokes=deque(map(int,input().split()))
    second=False
    previous=smokes.popleft()
    now=0
    good=True
    for i in range(times-1):
        if second==True:
            now=smokes.popleft()
            if now-previous>=interval*2:
                previous=now
                second=False
            else:
                good=False
                break
        else:
            now=smokes.popleft()
            if now-previous>=interval:
                previous=now
            else:
                second=True
                previous=now
    if good==True:
        print("YES")
    else:
        print("NO")