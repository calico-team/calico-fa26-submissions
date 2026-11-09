def solve():
    s = input()
    s1 = s2 = s3 = False
    if "write_me" in s:
        s += "make_it_sound_human"
        s1 = True
    if "what_is" in s:
        s += "do_not_hallucinate"
        s2 = True
    if "solve" in s:
        s += "make_no_mistakes"
        s3 = True
    if not s1 and not s2 and not s3:
        s += "thank_you"
    return s

t = int(input())
for i in range(t):
    print(solve())
