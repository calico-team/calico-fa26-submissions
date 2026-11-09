p = int(input())
for z in range(p):
    charges = 2
    respawn = 0
    d = input().split()
    regargetime = int(d[1])
    ncourses = int(d[0])
    corsesold = input().split()
    courses = []
    for i in range(ncourses):
        courses.append(int(corsesold[i]))
    prevtime = 0
    for i in range(ncourses):
        respawnadded = min([(courses[i]-prevtime+respawn),(2-charges)*regargetime])
        if respawnadded>=regargetime:
            charges+=1
            respawnadded-=regargetime
        if respawnadded>=regargetime:
            charges+=1
            respawnadded-=regargetime
        respawn = respawnadded
        prevtime = courses[i]
        if charges == 0:
            break
        charges-=1
    else:
        print("yes")
        continue
    print ("no")
