
def solve(N: int, K: int, A: list[str]) -> None:
    answer = [''] * N

    for ch in A:
        guess = ''.join(
            answer[i] if answer[i] else ch
            for i in range(N)
        )

        print_guess(guess)

        response = read_string()

        if response == "CORRECT":
            return

        for i in range(N):
            if response[i] != '_':
                answer[i] = response[i]

    print_guess(''.join(answer))
    response = read_string()

    if response == "CORRECT":
        return


def read_string():
    return input().strip()


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
