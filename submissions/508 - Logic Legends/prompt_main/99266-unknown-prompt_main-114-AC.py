def solve(Hal: str) -> str:
    if "write_me" in Hal:
        Hal = Hal + "make_it_sound_human"
    elif "what_is" in Hal:
        Hal = Hal + "do_not_hallucinate"
    elif "solve" in Hal:
        Hal = Hal + "make_no_mistakes"
    else:
        Hal = Hal + "thank_you"

    return Hal


def main():
    T = int(input())
    for _ in range(T):
        Hal = input()
        print(solve(Hal))


if __name__ == "__main__":
    main()