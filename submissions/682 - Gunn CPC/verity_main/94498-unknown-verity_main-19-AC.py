import sys

def solve():
    n, k = map(int, sys.stdin.readline().split())
    ls = sys.stdin.readline().split()

    answer = ['_'] * n

    for l in ls:
        guess = l * n
        print(guess, flush=True)

        result = sys.stdin.readline().strip()

        if result == "CORRECT":
            return

        for i in range(n):
            if result[i] == l:
                answer[i] = l

    print(''.join(answer), flush=True)
    sys.stdin.readline()


def main():
    t = int(sys.stdin.readline())

    for _ in range(t):
        solve()

if __name__ == "__main__":
    main()