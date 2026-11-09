testC = int(input())

for t in range(testC):
    firstLine = input().split()
    while len(firstLine) == 0:
        firstLine = input().split()
        
    n = int(firstLine[0])
    k = int(firstLine[1])
    
    xList = []
    yList = []
    zList = []
    dList = []
    
    droneGroups = {} 
    
    for i in range(n):
        Data = input().split()
        while len(Data) == 0:
            Data = input().split()
            
        x = int(Data[0])
        y = int(Data[1])
        
        xList.append(x)
        yList.append(y)
        zList.append(int(Data[2]))
        dList.append(Data[3])
        
        pathSum = x + y
        if pathSum not in droneGroups:
            droneGroups[pathSum] = []
        droneGroups[pathSum].append(i)
        
    totalRain = n * k
    
    for i in range(n):
        alwaysBlocked = False  
        blockedDays = set()
        
        currentPath = xList[i] + yList[i]
        
        for j in droneGroups[currentPath]:
            if i == j:
                continue
            
            if zList[j] > zList[i]:
                if dList[i] == dList[j]:
                    if xList[i] == xList[j] and yList[i] == yList[j]:
                        alwaysBlocked = True 
                elif dList[i] == 'E' and dList[j] == 'N':
                    t1 = xList[j] - xList[i]  
                    t2 = yList[i] - yList[j]  
                    if t1 == t2 and 0 <= t1 < k:
                        blockedDays.add(t1) 
                elif dList[i] == 'N' and dList[j] == 'E':
                    t1 = yList[j] - yList[i]  
                    t2 = xList[i] - xList[j]  
                    if t1 == t2 and 0 <= t1 < k:
                        blockedDays.add(t1) 
                        
        if alwaysBlocked == True:
            totalRain = totalRain - k
        else:
            totalRain = totalRain - len(blockedDays)

    print(totalRain)
