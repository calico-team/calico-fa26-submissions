def solve(N: int, K: int, A: list[str]) -> None:

    known = [None] * N

    for ch in A:

        guess = ""

        for i in range(N):
            if known[i] is not None:
                guess += known[i]
            else:
                guess += ch

        print_guess(guess)

        response = read_string()

        if response == "CORRECT":
            return

        for i in range(N):
            if response[i] != "_":
                known[i] = response[i]


def read_string():
    return input()


def print_guess(guess):
    print(guess, flush=True)


def main():
    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())
        A = input().split()

        solve(N, K, A)


if __name__ == '__main__':
    main()