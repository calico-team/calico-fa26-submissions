def solveProblem():
    inp = input()

    if "write_me" in inp:
        inp += "make_it_sound_human"
    elif "what_is" in inp:
        inp += "do_not_hallucinate"
    elif "solve" in inp:
        inp += "make_no_mistakes"
    else:
        inp += "thank_you"
    print(inp)


def main():
    testCase = int(input())
    for _ in range(testCase):
        solveProblem()


if __name__ == "__main__":
    main()
