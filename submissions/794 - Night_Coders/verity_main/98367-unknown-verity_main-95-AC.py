def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of gueses until you gues the answer string.
    You may use the read_string() and print_gues() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    gues = [A[0]] * N

    for _ in range(100):
        print_gues("".join(gues))

        respond = read_string()

        if respond == "CORRECT":
            return

        for i in range(N):
            if respond[i] != "_":
                gues[i] = respond[i]


            else:

                curr_index = A.index(gues[i])
                gues[i] =   A[(curr_index + 1) % K]
    pass

def read_string():
    """
    Reads a single string from standard input.
    """
    s = input()
    return s

def print_gues(gues):
    """
    Prints a gues to standard output and flushes the output stream buffer.
    """
    print(gues, flush=True)


def main():
    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())
        A = input().split()

        solve(N, K, A)


if __name__ == '__main__':
    main()
