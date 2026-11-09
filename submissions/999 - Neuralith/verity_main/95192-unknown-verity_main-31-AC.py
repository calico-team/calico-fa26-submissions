
import sys

def solve():
    input = sys.stdin.readline
    t = int(input())

    for _ in range(t):
        n, k = map(int, input().split())
        chars = input().split()

        guess = [chars[0]] * n
        index = [0] * n

        while True:
            print("".join(guess), flush=True)

            response = input().strip()

            if response == "CORRECT":
                break

            for i in range(n):
                if response[i] == "_":
                    index[i] += 1
                    if index[i] < k:
                        guess[i] = chars[index[i]]

if __name__ == "__main__":
    solve()
