
def solve(N, K, A):
    ans = [None] * N

    for c in A:
        guess = ''.join(x if x is not None else c for x in ans)

        print_guess(guess)
        result = read_string()

        if result == "CORRECT":
            return

        for i in range(N):
            if result[i] != '_':
                ans[i] = result[i]
