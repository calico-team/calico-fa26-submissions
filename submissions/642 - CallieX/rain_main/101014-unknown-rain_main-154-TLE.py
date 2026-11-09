testC = int(input())

for t in range(testC):
    firstLine = input().split()
    n = int(firstLine[0])
    k = int(firstLine[1])
    
    xList = []
    yList = []
    zList = []
    dList = []
    xySum = [] 
    
    for i in range(n):
        Data = input().split()
        x = int(Data[0])
        y = int(Data[1])
        
        xList.append(x)
        yList.append(y)
        zList.append(int(Data[2]))
        dList.append(Data[3])
        xySum.append(x + y) 
        
    totalRain = n * k
    
    for i in range(n):
        alwaysBlocked = False  
        
        for j in range(n):
            if i == j:
                continue
            
            if xySum[i] != xySum[j]:
                continue
            
            if zList[j] > zList[i]:
                if dList[i] == dList[j]:
                    if xList[i] == xList[j] and yList[i] == yList[j]:
                        alwaysBlocked = True 
                elif dList[i] == 'E' and dList[j] == 'N':
                    t1 = xList[j] - xList[i]  
                    t2 = yList[i] - yList[j]  
                    if t1 == t2 and 0 <= t1 < k:
                        totalRain = totalRain - 1
                elif dList[i] == 'N' and dList[j] == 'E':
                    t1 = yList[j] - yList[i]  
                    t2 = xList[i] - xList[j]  
                    if t1 == t2 and 0 <= t1 < k:
                        totalRain = totalRain - 1
                        
        if alwaysBlocked == True:
            totalRain = totalRain - k

    print(totalRain)
