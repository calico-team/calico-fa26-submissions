for i in range(int(input())):
    word=input()
    word=word.split()
    cd=int(word[1])
    word=input().split()
    cur=2
    time=0
    toreturn='YES'
    for j in range(len(word)):
        if cur<2:
            if time+(int(word[j])-int(word[j-1])) >= cd:
                cur+=1
            if time+(int(word[j])-int(word[j-1])) >= 2*cd:
                cur+=1
                time=time+(int(word[j])-int(word[j-1]))-cd
            time=time+(int(word[j])-int(word[j-1]))-cd
        if cur <1:
            toreturn='NO'
            break
        else:
            cur-=1
    print(toreturn)