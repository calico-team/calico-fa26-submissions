# Source: https://usaco.guide/general/io

def cool_func():
    N, R = map(int, input().split())
    smoke_times = list(map(int, input().split()))
    for i in range(1, N):
        if smoke_times[i]-smoke_times[i-1] < R:
            print("NO")
            return
    print("YES")
test_cases = int(input())
for i in range(test_cases):
    cool_func()
         