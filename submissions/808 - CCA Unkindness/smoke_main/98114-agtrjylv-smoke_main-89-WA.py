# Source: https://usaco.guide/general/io

def cool_func():
    smokes = 2
    
    N, R = map(int, input().split())
    smoke_times = list(map(int, input().split()))
    last_smoke = 0
    reached = False

    for x in smoke_times:
        passed = x - last_smoke
        regen_smokes = passed//R
        

        smokes = min(2, regen_smokes + smokes)

        if smokes>2:
            reached = True


        if smokes>0:
            smokes -= 1
        else:
            print("NO")
            return 
        
        if reached == True:
            last_smoke = x
        else:
            last_smoke = last_smoke + (regen_smokes * R)

    
        

    print("YES")
test_cases = int(input())
for i in range(test_cases):
    cool_func()
         