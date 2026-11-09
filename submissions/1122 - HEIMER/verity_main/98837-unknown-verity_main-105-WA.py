
def solve(N, K, A):
    known = [None] * N

    for c in A:
        guess = ''.join(known[i] if known[i] is not None else c
                        for i in range(N))

        print_guess(guess)
        response = read_string()

        if response == "CORRECT":
            return

        for i in range(N):
            if response[i] != '_':
                known[i] = response[i]
