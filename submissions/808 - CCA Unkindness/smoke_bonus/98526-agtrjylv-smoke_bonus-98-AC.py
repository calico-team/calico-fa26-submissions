# Source: https://usaco.guide/general/io

def cool_func():
    smokes = 2
    
    N, R = map(int, input().split())
    smoke_times = list(map(int, input().split()))
    next_time = -1
    

    for x in smoke_times:
        regen_smokes = 0

        if next_time != -1 and x >= next_time:
            regen_smokes = 1+ (x-next_time)//R
            smokes+= regen_smokes
    

        if smokes>=2:
            smokes =2
            next_time = -1
        else:
            next_time += regen_smokes * R


        if smokes>0:
            smokes -= 1
            if next_time == -1:
                next_time = x+R
        else:
            print("NO")
            return 
        

    
        

    print("YES")
test_cases = int(input())
for i in range(test_cases):
    cool_func()
         