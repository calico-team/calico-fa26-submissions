import sys
from bisect import bisect_left,bisect_right
data = sys.stdin.read().split()
pos = 0
tests= int(data[pos])
pos +=1
for i in range(tests):
    n = int(data[pos])
    k = int(data[pos+1])
    pos+=2
    east = {}
    north = {}
    for d in range(n):
        x = int(data[pos])
        y = int(data[pos+1])
        direction = data[pos+3]
        pos +=4
        group = x+y
        if direction == "E":
            east.setdefault(group, []).append(x)
        else:
            north.setdefault(group, []).append(x)
    meetings = 0
    for group in north:
        if group not in east:
            continue
        east_list = sorted(east[group])
        for x in north[group]:
            left = bisect_left(east_list, x- (k-1))
            right = bisect_right(east_list,x)
            meetings += right -left 
    print(n*k - meetings)
