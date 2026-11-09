from random import choice
def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    # YOUR CODE HERE
    g = []
    for i in range(N):
        g.append('_')
    # r = []
    # for i in range(N):
    #     r.append('_')

    for gusses in range(100):
        for i in range(N):
            if g[i] == '_':
                g[i] = choice(A)
        print_list(g)
        tip = read_string()
        if tip != 'CORRECT':
            for i in range(N):
                if g[i] != tip[i]:
                    g[i] = '_'
        else:
            break
    
def print_list(l):
    s = ''
    for i in l:
        s += i
    print(s)


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
