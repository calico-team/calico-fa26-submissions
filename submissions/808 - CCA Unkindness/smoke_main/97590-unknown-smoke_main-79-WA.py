# Source: https://usaco.guide/general/io

def cool_func():
    smokes = 2
    
    N, R = map(int, input().split())
    smoke_times = list(map(int, input().split()))
    last_smoke = smoke_times[0]
    for i in range(0, max(smoke_times)+1):
        if i in smoke_times:
            if smokes == 2:
                last_smoke = i
            if smokes>0:
                smokes = smokes -1
                
            else:
                print("NO")
                return
        if i - last_smoke == R and smokes<2:
            smokes+=1
            last_smoke = i

        

    print("YES")
test_cases = int(input())
for i in range(test_cases):
    cool_func()
         