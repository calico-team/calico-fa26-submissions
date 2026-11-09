import sys

def main():
    input = sys.stdin.readline

    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        letters = input().split()
        known = [None] * N
        for character in letters:
            guess = ''.join(known[i] if known[i] is not None else character
                            for i in range(N))
            print(guess)
            sys.stdout.flush()
            resp = input().strip()
            if resp == "CORRECT":
                break
            for i in range(N):
                if resp[i] != '_':
                    known[i] = resp[i]

main()