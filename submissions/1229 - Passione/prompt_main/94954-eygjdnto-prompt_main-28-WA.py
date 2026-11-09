

def solve(S):
    if "write_me" in S:
        return S + "make_it_sound_human"
    elif "what_is" in S:
        return S + "do_not_hallucinate"
    elif "solve" in S:
        return S + "make_no_mistakes"
    else:
        return S + "thank_you"
s = input()      
print(solve(s))