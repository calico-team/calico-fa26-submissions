T = int(input())

for _ in range(T):
    S = input()

    if "write_me" in S:
        S += "make_it_sound_human"

    elif "what_is" in S:
        S += "do_not_hallucinate"

    elif "solve" in S:
        S += "make_no_mistakes"

    else:
        S += "thank_you"

print(S)