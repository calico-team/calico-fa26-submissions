import sys
tests = int(input())
for i in range(tests):
    data = input().split()
    n = int(data[0])
    k = int(data[1])
    drones = []
    total = 0
    collected = 0
    for j in range(n):
        x,y,z,d = input().split()
        new = [int(x),int(y),int(z),d]
        drones.append(new)

    
    for l in range(k):
        
        for m in range(n):

            for o in range(n-1):
                            
                noself=drones.copy()
                noself.remove(noself[m])
                
                
                if noself[o][0]==drones[m][0] and noself[o][1]==drones[m][1]:
                    collected -=1
                    
            if drones[m][3] == "E":
                drones[m][0]+=1
            elif drones[m][3] == "N":
                drones[m][1]+=1
            
            
        collected += n
        
    print (collected)
    sys.stdout.flush()
    
        