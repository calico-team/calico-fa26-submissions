testC = int(input())
for t in range(testC):
    firstLine = input().split()
    totalSmokes = int(firstLine[0])
    rechargeTime = int(firstLine[1])
    
    timeList = []
    time = input().split()
    for x in time:
        timeList.append(int(x))
        
charges = 2
readyTime = -1
outputResult = "YES"

for currTime in timeList:
    while readyTime != -1 and readyTime <= currTime:
        charges = charges + 1
        if charges ==2:
            readyTime = -1
        else:
            readyTime = readyTime + rechargeTime
    if charges >=1:
        charges = charges - 1

        if readyTime == -1:
            readyTime = currTime + rechargeTime
    else:
        outputResult = "NO"
        break
    print(outputResult)
   
       

