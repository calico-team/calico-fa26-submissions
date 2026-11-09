t = int(input())

for i in range(t):
    s = input()
    good = False

    for i in range(len(s)):
        if s[i:i + 8] == "write_me" and i + 9 < len(s):
            s += "make_it_sound_human"
            good = True
            break
        elif s[i:i + 7] == "what_is" and i + 8 < len(s):
            s += "do_not_hallucinate"
            good = True
            break
        elif s[i:i + 5] == "solve" and i + 6 < len(s):
            s += "make_no_mistakes"
            good = True
            break

    if not good:
        s += "thank_you"

    print(s)