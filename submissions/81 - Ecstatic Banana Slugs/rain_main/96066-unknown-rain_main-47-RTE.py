tests = int(input())
for i in range(tests):
    data = input().split()
    n = int(data[0])
    k = int(data[1])
    drones = []
    total = 0
    for j in range(n):
        temp = input().split
        x = int(temp[0])
        y= int(temp[1])
        z= int(temp[2])
        new = [x,y,z]
        drones.append(new)
        
    for l in range(k):
        collected= 0
        for m in range(n):
            if drones[m][3] == "E":
                drones[m][0]+=1
            elif drones[m][3] == "N":
                drones[m][1]+=1
            for o in range(n-1):
                noself = drones.remove(drones[m])
                if noself[o][0]==drones[m][0] and noself[o][1]==drones[m][1]:
                    collected -=1
        collected += n
        total += collected
    print (total)
    
        