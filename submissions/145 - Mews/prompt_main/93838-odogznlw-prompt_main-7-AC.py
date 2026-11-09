t = int(input())

for _ in range(t):
    s = input()

    if "write_me" in s:
        s += "make_it_sound_human"
    elif "what_is" in s:
        s += "do_not_hallucinate"
    elif "solve" in s:
        s += "make_no_mistakes"
    else:
        s += "thank_you"

    print(s)
