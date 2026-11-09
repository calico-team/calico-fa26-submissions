T = int(input())

for i in range(T):
    N,K= map(int, input().split())
    east = {}
    north = {}
    for j in range(N):
        x,y,z,d = input().split()
        x,y,z = int(x),int(y),int(z)
        key = x+y
        if d == 'E':
            east.setdefault(key, []).append(x)
        else:
            north.setdefault(key, []).append(x)
    block = 0
    for key, drones in north.items():
        drones.sort()
    for key,drones in east.items():
        if key not in north:
            continue
        poss = north[key]
        for x in drones:
            left = 0
            right = len(poss)
            while left < right:
                mid = (left+right) // 2
                if poss[mid] < x:
                    left = mid+1
                else:
                    right = mid
            start = left
            left = 0
            right = len(poss)
            while left < right:
                mid = (left+right) // 2
                if poss[mid] < x + K:
                    left = mid+1
                else:
                    right = mid
            block += left-start

    print(N*K -block)
