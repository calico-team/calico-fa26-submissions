import sys


def classify_suffix(s: str) -> str:
    lower = s.lower()

    if "write_me" in lower:
        return "make_it_sound_human"
    if "solve" in lower:
        return "make_no_mistakes"
    if "what_is" in lower:
        return "do_not_hallucinate"
    return "thank_you"


def solve() -> None:
    data = sys.stdin.read().splitlines()
    if not data:
        return

    t = int(data[0].strip())
    out = []

    for i in range(1, t + 1):
        if i >= len(data):
            break
        s = data[i].rstrip()
        out.append(s + classify_suffix(s))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()