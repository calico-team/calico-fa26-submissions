from sys import stdin


n = int(stdin.readline())
for _ in range(n):
    # fsdf
    p = stdin.readline().strip()
    if "write_me" in p:
        p += "make_it_sound_human"
    elif "what_is" in p:
        p += "do_not_hallucinate"
    elif "solve" in p:
        p += "make_no_mistakes"
    else:
        p += "thank_you"
    print(p)
