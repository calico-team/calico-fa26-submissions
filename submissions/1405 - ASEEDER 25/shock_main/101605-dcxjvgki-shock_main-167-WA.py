import sys


def solve() -> None:
    data = sys.stdin.buffer.read().splitlines()
    if not data:
        return

    t = int(data[0].strip())
    answers = []

    for i in range(1, t + 1):
        s = data[i].decode().strip()

        if "write_me" in s:
            s += "make_it_sound_human"
        elif "what_is" in s:
            s += "do_not_hallucinate"
        elif "solve" in s:
            s += "make_no_mistakes"
        else:
            s += "thank_you"

        answers.append(s)

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    solve()
