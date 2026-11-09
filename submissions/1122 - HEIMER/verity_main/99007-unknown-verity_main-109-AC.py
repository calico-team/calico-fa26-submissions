def solve(N, K, A):
    known = [None] * N
    for c in A:
        print_guess(''.join(k or c for k in known))
        resp = read_string()
        if resp == "CORRECT":
            return
        known = [r if r != '_' else k for r, k in zip(resp, known)]


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