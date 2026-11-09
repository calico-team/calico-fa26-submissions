def solve(N: int, K: int, A: list[str]) -> None:
    ans= '_'*N
    for c in A:
        G= ans.replace('_',c)
        print_guess(G)
        R =read_string()
        if R =='CORRECT':
            break
        ans =R

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
