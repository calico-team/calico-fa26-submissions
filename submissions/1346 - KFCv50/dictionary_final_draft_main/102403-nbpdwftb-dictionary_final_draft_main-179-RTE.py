T = int(input())
for _ in range (T) :
    N,M,K=list(map(int,input().split()))
    A=list(map(int,input().split()))
    result = 0
    for i in A:
        if i == 0:
            result += 1
    print(result)
             
        
