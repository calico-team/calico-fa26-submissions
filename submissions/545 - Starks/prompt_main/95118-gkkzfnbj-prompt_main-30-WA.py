
T = int(input())

for i in range(T):
    S = input()

    if "write_me" in S:
        S = S + "_make_it_sound_human"

    elif "what_is" in S:
        S = S + "_do_not_hallucinate"

    elif "solve" in S:
        S = S + "_make_no_mistakes"

    else:
        S = S + "_thank_you"

    print(S)
