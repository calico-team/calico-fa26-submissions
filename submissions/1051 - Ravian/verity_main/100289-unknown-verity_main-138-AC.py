def solve(N: int, K: int, A: list[str]) -> None:
    new_known = ['_'] * N

    for i in range(K-1):
        current_guess = A[i] * N
        print_guess(current_guess)
        evaluate = read_string()

        if evaluate == "CORRECT":
            return

        for j in range(N):
            if evaluate[j] != '_':
                new_known[j] = evaluate[j]

    for z in range(N):
        if new_known[z] == '_':
            new_known[z] = A[-1]

    print_guess("".join(new_known))
    read_string()



def read_string():
    """
    Reads a single string from standard input.
    """
    s = input()
    return s

def print_guess(guess):
    """
    Prints a guess to standard output and flushes the output stream buffer.
    """
    print(guess, flush=True)


def main():
    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())
        A = input().split()

        solve(N, K, A)


if __name__ == '__main__':
    main()