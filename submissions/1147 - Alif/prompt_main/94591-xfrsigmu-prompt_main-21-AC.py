import sys

def modify(s):
    if "write_me" in s:
        return s + "make_it_sound_human"
    if "what_is" in s:
        return s + "do_not_hallucinate"
    if "solve" in s:
        return s + "make_no_mistakes"
    return s + "thank_you"

def main():
    d = sys.stdin.read().split()
    T = int(d[0])
    res = []
    for i in range(1, T + 1):
        res.append(modify(d[i]))
    sys.stdout.write("\n".join(res))

if __name__ == "__main__":
    main()