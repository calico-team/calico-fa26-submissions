#input parsing
def parseSpacedInts(inputStream):
    tokens = inputStream.split()
    
    for i in range(len(tokens)):
        try:
            tokens[i] = int(tokens[i])
        except ValueError:
            tokens[i] = tokens[i]
    
    return tokens



#the actual algorithm
#input processing works. I tested it.
for _ in range(int(input())):
    testCasePrefix = parseSpacedInts(input())
    numDrones = testCasePrefix[0]
    numNights = testCasePrefix[1]
    
    droneData = []
    for droneNum in range(numDrones):
        thisDroneStuff = parseSpacedInts(input())
        droneData.append(thisDroneStuff)
    
    #input processing done
    #the solving
    totalRainwater = 0
    for __ in range(numNights):
        xyCoords = []
        for thisDrone in droneData:
            thisPos = [thisDrone[0], thisDrone[1]]
            if thisPos not in xyCoords:
                xyCoords.append(thisPos)
        totalRainwater += len(xyCoords)
        
        for thisDrone in droneData:
            if thisDrone[3]=="N":
                thisDrone[1]+=1
            elif thisDrone[3]=="E":
                thisDrone[0]+=1
            else:
                pass
    
    #output
    print(totalRainwater)









