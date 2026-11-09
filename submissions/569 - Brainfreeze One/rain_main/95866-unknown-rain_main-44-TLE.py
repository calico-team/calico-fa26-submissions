t = int(input()) # cases
queries = []
ni = []

for i in range(t):
    n, k = [int(num) for num in input().split()]
    tst = []
    for j in range(n):
        inp = input().split()
        x = int(inp[0])
        y = int(inp[1])
        height = int(inp[2])
        dir = inp[3]
        tst.append([height, [x, y, dir]])
        
    queries.append(tst)
    ni.append(k)

res = []

for i in range(len(queries)):
    case = queries[i]
    cur = 0
    for j in range(ni[i]):
        seen = set()
        for drone in case:
            height, dih = drone
            if (dih[0], dih[1]) not in seen:
                seen.add((dih[0], dih[1]))
            
        cur += len(seen)
    
        for drone in case:
            if drone[1][2] == "E":
                drone[1][0] += 1
            else:
                drone[1][1] += 1
    res.append(cur)

for it in res:
    print(it)
    
            
        
        