def solve(s: str) -> str:
    if "write_me" in s:
        s = s + "_make_it_a_great_human"

    elif "what_if" in s:
        s = s + "_do_not_hallucinate"

    elif "solve" in s:
        s = s + "_do_not_make_mistakes"

    else:
        s = s + "_thank_you"

    return s

def main():
    T = int(input())
    for _ in range(T):
        s = input()
        print(solve(s))

if __name__ == "__main__":
    main()