T = int(input())

for i in range(T):
    s = input()

    if "write_me" in s:
        s += "_make_it_sound_human"
    elif "what_is" in s:
        s += "_do_not_hallucinate"
    elif "solve" in s:
        s += "_make_no_mistakes"
    else:
        s += "_thank_you"

    print(S)