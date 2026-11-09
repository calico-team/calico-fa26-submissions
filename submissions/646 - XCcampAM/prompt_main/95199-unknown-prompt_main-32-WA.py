q=int(input())
for i in range(q):
    s=list(input())
    si="Hello, World!"
    for i in range(len(s)-5):
        if i>=len(s)-5:
            break
        si=str(s[i]+s[i+1]+s[i+2]+s[i+3]+s[i+4]+s[i+5])
        if si=="solve":
            s.append("make_no_mistakes")
            print("".join(s))
            exit()
    for i in range(len(s)-8):
        if i>=len(s)-8:
            break
        si=str(s[i]+s[i+1]+s[i+2]+s[i+3]+s[i+4]+s[i+5]+s[i+6]+s[i+7]+s[i+8])
        if si=="what_is_":
            s.append("do_not_hallucinate")
            print("".join(s))
            exit()
        if si=="write_me":
            s.append("make_it_sound_human")
            print("".join(s))
            exit()
    s.append("thank_you")
    print("".join(s))
    exit()
