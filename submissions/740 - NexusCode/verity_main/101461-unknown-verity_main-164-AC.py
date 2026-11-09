
def solve(N: int, K: int, A: list[str]) -> None:
    result = ['_'] * N

    for ch in A:
        guess = ""

        for i in range(N):
            if result[i] != '_':
                guess += result[i]
            else:
                guess += ch

        print(guess, flush=True)

        response = input().strip()

        if response == "CORRECT":
            return

        for i in range(N):
            if response[i] != '_':
                result[i] = response[i]


def main():
    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())
        A = input().split()

        solve(N, K, A)


if __name__ == '__main__':
    main()
