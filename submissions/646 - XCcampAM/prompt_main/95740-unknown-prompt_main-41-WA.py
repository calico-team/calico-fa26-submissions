q=int(input())
for i in range(q):
    m=True
    s=list(input())
    si="Hello, World!"
    for i in range(len(s)-6):
        if i>=len(s)-5:
            break
        si=str(s[i]+s[i+1]+s[i+2]+s[i+3]+s[i+4])
        if si=="solve":
            s.append("make_no_mistakes")
            print("".join(s))
            m=False
            break
    if m: 
        for i in range(len(s)-9):
            if i>=len(s)-8:
                break
            si=str(s[i]+s[i+1]+s[i+2]+s[i+3]+s[i+4]+s[i+5]+s[i+6]+s[i+7])
            if si=="what_is_":
                m=False
                s.append("do_not_hallucinate")
                print("".join(s))
                break
            if si=="write_me":
                m=False
                s.append("make_it_sound_human")
                print("".join(s))
                break
    if m:
        s.append("thank_you")
        print("".join(s))
