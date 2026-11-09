import sys

def solve():
    input = sys.stdin.readline

    T = int(input())

    for _ in range(T):
        N, K = map(int, input().split())
        A = input().split()

        # Store discovered characters
        ans = [None] * N

        # Try each available character
        for ch in A:

            # Construct the next guess
            guess = ''.join(
                ans[i] if ans[i] is not None else ch
                for i in range(N)
            )

            # Submit guess
            print(guess, flush=True)

            # Read judge response
            response = input().strip()

            if response == "CORRECT":
                break

            # Save correctly guessed positions
            for i in range(N):
                if response[i] != '_':
                    ans[i] = response[i]


if __name__ == "__main__":
    solve()