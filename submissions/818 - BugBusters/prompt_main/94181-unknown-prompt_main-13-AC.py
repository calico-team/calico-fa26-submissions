import sys

def solve():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    t = int(data[0])
    out = []
    for i in range(1, t + 1):
        s = data[i]
        if "write_me" in s:
            s += "make_it_sound_human"
        elif "what_is" in s:
            s += "do_not_hallucinate"
        elif "solve" in s:
            s += "make_no_mistakes"
        else:
            s += "thank_you"
        out.append(s)
    sys.stdout.write("\n".join(out))

if __name__ == "__main__":
    solve()
