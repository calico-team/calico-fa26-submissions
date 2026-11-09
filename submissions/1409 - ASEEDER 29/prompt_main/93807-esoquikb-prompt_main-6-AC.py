from pickletools import long1

t = int(input())
for T in range(t):
    s = input()
    b = True
    if "write_me" in s:
        s += "make_it_sound_human "
        b = False
    if "what_is" in s:
        s += "do_not_hallucinate"
        b = False
    if "solve" in s:
        s += "make_no_mistakes"
        b = False
    if b:
        s += "thank_you"

    print(s)


