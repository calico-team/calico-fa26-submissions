def solve(N: int, K: int, A: list[str]) -> None:
    """
    Print a sequence of guesses until you guess the answer string.
    You may use the read_string() and print_guess() helper functions defined below.

    N: Length of the string
    K: Number of different -ities
    A: List containing the different -ities
    """
    answer = [None] * N
    for c in A:
        guess = ''
        for i in range(N):
            if answer[i] is not None:
                guess += answer[i]
            else:
                guess += c
        print(guess, flush=True)
        response = input()
        if response == "CORRECT":
            return
        for i in range(N):
            if response[i] != '_':
                answer[i] = response[i]
    print(''.join(answer), flush=True)
    input()


def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        A = input().split()
        solve(N, K, A)


if __name__ == '__main__':
    main()
