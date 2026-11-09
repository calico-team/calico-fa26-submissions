from collections import deque
t = int(input())
for i in range(t):
    n, k = map(int,input().split())
    count = 0
    l = []
    for i in range(n):
        x, y, z, d = input().split()
        x, y, z = int(x), int(y), int(z)
        l.append([x,y,z,d])
    for i in range(k):
        s = set()
        for j in range(n):
            s.add((l[j][0],l[j][1]))
            #print(s)
            if l[j][3] == "E":
                l[j][0]+=1
            if l[j][3] == "N":
                l[j][1]+=1
        count += len(s)
    print(count)
