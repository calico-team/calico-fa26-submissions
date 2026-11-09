T = int(input())
for _ in range(T):
    S = input()
    if "write_me" in S:
        new_str = S + "make_it_sound_human"
    elif "what_is" in S:
        new_str = S + "do_not_hallucinate"
    elif "solve" in S:
        new_str = S + "make_no_mistakes"
    else:
        new_str = S + "thank_you"
    print(new_str)
