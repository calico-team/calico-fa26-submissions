dih = int(input())
for i in range(dih):
    a = input()
    if "write_me" in a:
        a += "make_it_sound_human"
    elif "what_is" in a:
        a += "do_not_hallucinate"
    elif "solve" in a:
        a += "make_no_mistakes"
    else:
        a += "thank you"  
    print(a)