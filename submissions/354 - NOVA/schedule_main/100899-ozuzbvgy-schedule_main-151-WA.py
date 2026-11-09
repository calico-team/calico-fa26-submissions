a = int(input())

for i in range(a):
    n,m,k = map(int,input().split())
    
    lst = list(map(int,input().split()))
    
    matrix = [False] * n
    
    course = 0

    
    
    for z in range(m):
        
        classes = 0
        for j in range(n):
            if lst[j] == 0 and classes < k:
                classes += 1
                lst[j] -= 1
        
        
        for l in range(n):
            if lst[l] < 0 and matrix[l] == False:
                course += 1
                matrix[l] = True
                for d in range(n):
                    if lst[d] - 1 == l:
                        lst[d] = 0
    
    print(course) 
    
    