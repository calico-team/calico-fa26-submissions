def solve():
    test_cases = int(input())

    for case_num in range(test_cases):
        n, k = map(int, input().split())
        possible_letters = input().split()

        known = [''] * n

        for ch in possible_letters:
            current_guess = ''.join(
                known[i] if known[i] else ch
                for i in range(n)
            )

            print(current_guess, flush=True)

            judge_reply = input().strip()

            if judge_reply == "CORRECT":
                break

            for i in range(n):
                if judge_reply[i] != '_':
                    known[i] = judge_reply[i]


if __name__ == "__main__":
    solve()