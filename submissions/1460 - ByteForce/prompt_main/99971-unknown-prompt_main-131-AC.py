import sys


def solve(s: str) -> str:
    if "write_me" in s:
        return s + "make_it_sound_human"
    elif "what_is" in s:
        return s + "do_not_hallucinate"
    elif "solve" in s:
        return s + "make_no_mistakes"
    else:
        return s + "thank_you"


def main():
    data = sys.stdin.read().splitlines()
    if not data:
        return
    t = int(data[0].strip())
    for i in range(1, t + 1):
        s = data[i].strip()
        print(solve(s))


if __name__ == "__main__":
    main()
