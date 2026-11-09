import sys

def fix_prompt(s):
    if "write_me" in s:
        return s + "make_it_sound_human"
    if "what_is" in s:
        return s + "do_not_hallucinate"
    if "solve" in s:
        return s + "make_no_mistakes"
    return s + "thank_you"

def main():
    lines = sys.stdin.read().split()
    t = int(lines[0])
    for k in range(1, t + 1):
        print(fix_prompt(lines[k]))

main()