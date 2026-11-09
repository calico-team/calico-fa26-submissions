
import sys

def solve():
    data = sys.stdin.read().split()
    t = int(data[0])

    ans = []

    for s in data[1:t+1]:
        if "write_me" in s:
            s += "make_it_sound_human"
        elif "what_is" in s:
            s += "do_not_hallucinate"
        elif "solve" in s:
            s += "make_no_mistakes"
        else:
            s += "thank_you"

        ans.append(s)

    sys.stdout.write("\n".join(ans))

if __name__ == "__main__":
    solve()
