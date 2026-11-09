
tests = int(input())
for i in range(tests):
    data = input().split()
    n = int(data[0])
    k = int(data[1])
    x=[]
    y=[]
    d=[]
    total = 0
    
    for j in range(n):
        temp = input().split()
        x.append(int(temp[0]))
        y.append(int(temp[1]))
        d.append(temp[3])
    
    for l in range(k):
        for m in range(n):
            if x.count(x[m])>=2 and y.count(y[m])>=2:
                total-=1
            if d[m] == "E":
                x[m]+=1
            elif d[m] == "E":
                y[m]+=1
        total+=n
        
            
        
        
    print(total)
    
        