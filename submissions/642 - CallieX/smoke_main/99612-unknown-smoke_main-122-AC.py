testC = int(input())

for t in range(testC):
    
    firstline = input().split()
    n = int(firstline[0])
    r = int(firstline[1])
    
    Sline = input().split()
    timesList = []
    for element in Sline:
        timesList.append(int(element))
        
    charges = 2
    readyTime = -1 
    Result = "YES"
    
    for currTime in timesList:
        
        
        while readyTime != -1 and readyTime <= currTime:
            charges = charges + 1
            if charges == 2:
                readyTime = -1  
            else:
                readyTime = readyTime + r  
                
        if charges >= 1:
            charges = charges - 1
            
            if readyTime == -1:
                readyTime = currTime + r
        else:
            Result = "NO"
            break  
    print(Result)
