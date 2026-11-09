def solve(N: int, K: int, A: list[str]) -> None:
    known = ['_'] * N
    for c in A:
        guess = ''.join(x if x != '_' else c for x in known)
        print_guess(guess)
        result = read_string()
        if result == 'CORRECT':
            return
        for i, x in enumerate(result):
            if x != '_':
                known[i] = x


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
