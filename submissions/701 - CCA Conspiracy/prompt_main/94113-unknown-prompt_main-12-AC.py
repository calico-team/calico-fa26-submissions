t=int(input())
for asdf in range(t):
    cur=input()
    lst=[]
    for j in cur:
        lst+=[j]
    x=len(lst)
    s1='write_me'
    s2='what_is'
    s3='solve'
    s4='make_it_sound_human'
    s5='do_not_hallucinate'
    s6='make_no_mistakes'
    s7='thank_you'
    l1=[]
    l2=[]
    l3=[]
    l4=[]
    l5=[]
    l6=[]
    l7=[]
    for i in s1:
        l1+=[i]
    for i in s2:
        l2+=[i]
    for i in s3:
        l3+=[i]
    for i in s4:
        l4+=[i]
    for i in s5:
        l5+=[i]
    for i in s6:
        l6+=[i]
    for i in s7:
        l7+=[i]
    work=False
    for j in range(x-8):
        work=True
        for i in range(8):
            if lst[j+i]!=l1[i]:
                work=False
        if work==True:
            break
    if work==True:
        lst+=l4
    else:
        work=False
        for j in range(x-7):
            work=True
            for i in range(7):
                if lst[j+i]!=l2[i]:
                    work=False
            if work==True:
                break
        if work==True:
            lst+=l5
        else:
            work=False
            for j in range(x-5):
                work=True
                for i in range(5):
                    if lst[j+i]!=l3[i]:
                        work=False
                if work==True:
                    break
            if work==True:
                lst+=l6
            else:
                lst+=l7
    s=''
    for j in lst:
        s+=j
    print(s)