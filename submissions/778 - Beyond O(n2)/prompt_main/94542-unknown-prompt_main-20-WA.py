t = int(input())

for _ in range(t):
    s = input().strip()

    if "write_me" in s:
        ending = "make_it_sound_human"
    elif "what_is" in s:
        ending = "do_not_hallucinate"
    elif "solve" in s:
        ending = "make_no_mistakes"
    else:
        ending = "thank_you"

    print(s + "_" + ending)