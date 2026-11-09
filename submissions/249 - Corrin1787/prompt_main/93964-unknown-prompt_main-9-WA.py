S = str(input())
flag = True
if "write_me" in S:
    S = S + "make_it_sound_human"
    flag = False
if "what_is" in S:
    S = S + "do_not_hallucinate"
    flag = False
if "solve" in S:
    S = S + "make_no_mistakes"
    flag = False
if flag:
    S = S + "thank_you"
print(S)
