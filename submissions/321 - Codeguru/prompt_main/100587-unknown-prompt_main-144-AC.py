def solve(s):
    if "write_me" in s:
        return s + "make_it_sound_human"
    elif "what_is" in s:
        return s + "do_not_hallucinate"
    elif "solve" in s:
        return s + "make_no_mistakes"
    else:
        return s + "thank_you"

t = int(input())
for _ in range(t):
    s = input().strip()
    print(solve(s))