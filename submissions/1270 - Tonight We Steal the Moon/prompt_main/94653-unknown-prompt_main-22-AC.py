def solve():
    import sys
    input = sys.stdin.read
    data = input().split()

    if not data:
        return

    t = int(data[0])
    results = []

    for i in range(1, t + 1):
        S = data[i]

        if "write_me" in S:
            S += "make_it_sound_human"
        elif "what_is" in S:
            S += "do_not_hallucinate"
        elif "solve" in S:
            S += "make_no_mistakes"
        else:
            S += "thank_you"

        results.append(S)

    print('\n'.join(results))


if __name__ == '__main__':
    solve()
