testcases = int(input())
results = []

for case in range(testcases):
    flag = False
    N, R = [int(x) for x in input().split()]
    A = [int(x) for x in input().split()]
    restoreTime = [0, 0]
    charge = 0
    
    for i in range(len(A)):
        if restoreTime[charge] <= A[i]:
            restoreTime[charge] = max(A[i], restoreTime[1 - charge]) + R
            charge = 1 - charge
        else:
            results.append("NO")
            flag = True
            break
    
    if flag:
        continue
    
    results.append("YES")
    

for result in results:
    print(result)
    