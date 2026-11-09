def solve(N):
    if "write_me" in N:
        return N + "make_it_sound_human"
    elif "what_is" in N:
        return N + "do_not_hallucinate"
    elif "solve" in N:
        return N + "make_no_mistakes"
    else:
        return N + "thank_you"
    


def main():
    test_cases = int(input())
    strings = [input() for _ in range(test_cases)]
    for N in strings:
        print(solve(N))

if __name__ == '__main__':
    main()