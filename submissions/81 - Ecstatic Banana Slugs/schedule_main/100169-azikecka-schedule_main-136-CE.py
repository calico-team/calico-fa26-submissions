p = int(input())
for z in range(p):
    data = int(input())
    semesters = data[1]
    maxcorses = data[2]
    stuff = input().split()
    bstuff = []
    for i in range(len(stuff)):
        bstuff.append(stuff[i])
    duhlist = []
    for i in range(len(stuff)):
        duhlist.append(bstuff.count(i))
        ok = True
    for i in range(len(stuff)):
        if ok and duhlist[i]!=0:
            continue
        else:
            duhlist[i] = 0
            ok = False
    #start the simulation GO  BEARS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    courses = 0
    for i in range(semesters):
        for j in range(i+1)
            courses+=min([maxcorses,duhlist[j]])
            duhlist[j]-=min([maxcorses,duhlist[j]])
    print(courses):