t=int(input())


for i in range(t):
    n,k = map(int,input().split())
    drone=[]
    # space=[[[]]]
    line={}
    ans=n*k
    if k==5:
        pass
    for j in range(n):
        s=input().split()
        drone.append([*map(int,s[:3]),s[3]])
        # space[drone[0]][drone[1]][drone[2]]=drone[3]
        if drone[j][3]=="N":
            if (drone[j][1]+drone[j][0]) in line.keys():
                line[drone[j][1] + drone[j][0]].append(drone[j])
            else:
                line[drone[j][1]+drone[j][0]] = [drone[j]]
    for j in range(n):
        if drone[j][3]=="E":
            # print(drone[j][1]+drone[j][0],flush=True)
            if drone[j][1]+drone[j][0] in line.keys():
                for s in line[drone[j][1]+drone[j][0]]:
                    if drone[j][1] - s[1]<=k-1:
                        ans-=1
                        # print(str(drone[j])+" "+str(line[drone[j][1]+drone[j][0]]),flush=True)
                    # else:
                        # print("NO",s,drone[j],drone[j][1] - s[1],k,flush=True)

    # print(line,flush=True)
    print(ans,flush=True)
    # print("----------------------",flush=True)

