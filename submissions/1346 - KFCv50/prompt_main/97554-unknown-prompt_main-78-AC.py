w=int(input())
for i in range(w):
    a=input()
    b="write_me"
    c="what_is"
    d="solve"
    e=[a]

    if b in a:
        e.append("make_it_sound_human")
    elif c in a:
        e.append("do_not_hallucinate")
    elif d in a:
        e.append("make_no_mistakes")
    else:
        e.append("thank_you")
    print("".join(e))
        
