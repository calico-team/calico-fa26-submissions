a = int(input())

for i in range(a):
    n,m,k = map(int,input().split())
    
    lst = list(map(int,input().split()))
    
    matrix = [False] * n
    
    course = 0

    for _ in range(m):
        
        temp = []
        
        classes = 0
        for j in range(n):
            if lst[j] == 0 and classes < k and matrix[j] == False:
                temp.append(j)
                classes += 1
                
        
        
        for l in temp:
            
            course += 1
            matrix[l] = True
            
            for d in range(n):
                if lst[d] - 1 == l:
                    lst[d] = 0
    
    print(course) 
    
    