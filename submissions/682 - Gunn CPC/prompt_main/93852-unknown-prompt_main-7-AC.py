t = int(input())

for _ in range(t):
    s = input()
    out = s

    if s.find("write_me") != -1:
        out += "make_it_sound_human"
    if s.find("what_is") != -1:
        out += "do_not_hallucinate"
    if s.find("solve") != -1:
        out += "make_no_mistakes"
    if s.find("solve") == -1 and s.find("write_me") == -1 and s.find("what_is") == -1:
        out += "thank_you"
    print(out)