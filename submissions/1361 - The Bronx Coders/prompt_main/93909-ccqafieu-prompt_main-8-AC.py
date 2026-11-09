import sys

def solve(s):
    if "write_me" in s:
        return s + "make_it_sound_human"
    if "what_is" in s:
        return s + "do_not_hallucinate"
    if "solve" in s:
        return s + "make_no_mistakes"
    return s + "thank_you"

def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    print("\n".join(solve(s) for s in data[1:1 + t]))

main()
