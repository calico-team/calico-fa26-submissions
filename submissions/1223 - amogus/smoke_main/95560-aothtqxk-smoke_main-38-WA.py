t = int(input())

allfinalanswers = []
count = 0
for i in range(t):
    able = False
    numberofrequests, reloadtime = input().split()
    numberofrequests = int(numberofrequests)
    reloadtime = int(reloadtime)

    lelistpart2 = input().split()

    while(count<(len(lelistpart2))-1):
        if int(lelistpart2[count+1]) - int(lelistpart2[count]) < reloadtime:
            able = False

            break

        if int(lelistpart2[count+1]) - int(lelistpart2[count]) >= reloadtime:
            able = True


        count+=1


    
    if able == True:
        allfinalanswers.append("YES")

    else:
        allfinalanswers.append("NO")
    count = 0

for i in allfinalanswers:
    print(i)




