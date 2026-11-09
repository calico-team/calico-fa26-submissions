import difflib

def modify_prompt(S):
    if "write_me" in S:
        return S+"make_it_sound_human"
    elif "what_is" in S:
        return S+"do_not_hallucinate"
    elif "solve" in S:
        return S+"make_no_mistakes"
    else:
        return S+"thank_you"

if __name__=="__main__":
    S=input().strip()
    print(modify_prompt(s))
