t = int(input())

allfinalanswers = []
count = 0
for i in range(t):
    able = False
    bigable = True
    numberofrequests, reloadtime = input().split()
    numberofrequests = int(numberofrequests)
    reloadtime = int(reloadtime)

    lelistpart2 = input().split()
    while(len(lelistpart2)>numberofrequests):
        lelistpart2.pop()
        

    while(count<(len(lelistpart2))-1):
        if int(lelistpart2[count+1]) - int(lelistpart2[count]) < reloadtime:
            able = False
            bigable = False

        if int(lelistpart2[count+1]) - int(lelistpart2[count]) >= reloadtime:
            able = True
            #larger or equals to the needed time
        count+=1


    
    if able == True:
        allfinalanswers.append("YES")

    if bigable == False:
        allfinalanswers.append("NO")
    count = 0


for i in allfinalanswers:
    print(i)




