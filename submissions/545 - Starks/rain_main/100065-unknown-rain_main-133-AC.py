
import sys 
from bisect import bisect_left,bisect_right
data=iter(sys.stdin.buffer.read().split())

# number of test cases
T =int(next(data))
results=[]

#process every test case 
for _ in range(T):
    N = int(next(data))
    K = int(next(data))
    groups={}

    #read every drone 
    for i in range(N):
        x = int (next(data))
        y=int (next(data))
        z = int(next(data))
        direction = next(data)

        # calculate sum
        s = x+y

        if s not in groups: 
            groups[s] = [[],[]]

        if direction == b'E':
            groups[s][0].append(x)
        else:
            groups[s][1].append(x)

    #count meetings
    meetings = 0

    for east_x, north_x in groups.values():
        if not east_x or not north_x:
            continue

        north_x.sort()

        for x_e in east_x:
            left= bisect_right(north_x,x_e)
            right = bisect_left(north_x,x_e + K)
            meetings +=right - left

    total_rain = N * K
    answer =total_rain - meetings
    results.append(str(answer))

print("\n".join(results))
