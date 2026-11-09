for i in range(int(input())):
    cd=int((input().split())[1])
    word=input().split()
    output='YES'
    next=0
    cur=2
    for j in range(len(word)):
        if cur<2:
            if int(word[j])>=next and cur ==1:
                cur+=1
                while next<int(word[j]):
                   next+=cd
            if int(word[j])>=next and cur ==0:
                if int(word[j])-2*cd > next:
                    cur+=2
                while next<int(word[j]):
                    next+=cd
        if cur<1:
            output='NO'
            break
        if cur >0:
            cur-=1
            next=int(word[j])+cd
    print(output)