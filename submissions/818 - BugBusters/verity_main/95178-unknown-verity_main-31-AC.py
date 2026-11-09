import sys

def solve():
    input = sys.stdin.readline

    t = int(input())

    for _ in range(t):
        n, k = map(int, input().split())
        alphabet = input().split()

        known = ['?'] * n

        for ch in alphabet:
            # Keep already discovered characters; try ch in every unknown position.
            guess = ''.join(known[i] if known[i] != '?' else ch
                            for i in range(n))

            print(guess, flush=True)

            response = input().strip()

            if response == "CORRECT":
                break

            # The judge reveals every position guessed correctly.
            for i, result_ch in enumerate(response):
                if result_ch != '_':
                    known[i] = result_ch


if __name__ == "__main__":
    solve()
