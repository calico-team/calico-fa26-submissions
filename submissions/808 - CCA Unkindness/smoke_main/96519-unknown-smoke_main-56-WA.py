# Source: https://usaco.guide/general/io
smokes = 1
def cool_func():
    global smokes
    N, R = map(int, input().split())
    smoke_times = list(map(int, input().split()))
    for i in range(1, N):
        if smoke_times[i]-smoke_times[i-1] < R and smokes==0:
            print("NO")
            return
        elif smoke_times[i]-smoke_times[i-1] < R and smokes!=0:
            smokes = smokes -1
        elif smoke_times[i]-smoke_times[i-1] >= R:
            smokes = smokes +1
    print("YES")
test_cases = int(input())
for i in range(test_cases):
    cool_func()
         