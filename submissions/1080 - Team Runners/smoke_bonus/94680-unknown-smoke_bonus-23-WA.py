testcases = int(input())
results = []

for case in range(testcases):
    flag = False
    N, R = [int(x) for x in input().split()]
    A = [int(x) for x in input().split()]
    
    for i in range(len(A) - 1):
        if A[i] + R > A[i + 1]:
            results.append("NO")
            flag = True
            break
    
    if flag:
        continue
    
    results.append("YES")
    
    
    
for result in results:
    print(result)
    