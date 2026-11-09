import sys

def solve(s):
    if "write_me" in s:
        return s + "make_it_sound_human"
    if "what_is" in s:
        return s + "do_not_hallucinate"
    if "solve_" in s:
        return s + "make_no_mistakes"
    return s + "thank_you"

# no spaces in the prompts so split is fine
data = sys.stdin.read().split()
n = int(data[0])
for i in range(1, n + 1):
    print(solve(data[i]))
