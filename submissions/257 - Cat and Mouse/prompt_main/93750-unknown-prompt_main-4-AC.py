T = int(input())
for i in range(T):
    s = input()
    if s.find("write_me") != -1:
        s += "make_it_sound_human"
    elif s.find("what_is") != -1:
        s += "do_not_hallucinate"
    elif s.find("solve") != -1:
        s += "make_no_mistakes"
    else:
        s += "thank_you"

    print(s)    
