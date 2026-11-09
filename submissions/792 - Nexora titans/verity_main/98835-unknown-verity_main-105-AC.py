import sys

def solve():
    input = sys.stdin.readline

    T = int(input())

    for item in range(T):
        N, K = map(int, input().split())
        chars = input().split()

        answer = ['?'] * N

        for ch in chars[:-1]:
            guess = ch * N
            print(guess, flush=True)

            responses = input().strip()

            if responses == "CORRECT":
                break

            for i in range(N):
                if responses[i] != '_':
                    answer[i] = responses[i]

        else:
            lastt = chars[-1]

            for i in range(N):
                if answer[i] == '?':
                    answer[i] = lastt

            print(''.join(answer), flush=True)

            responses = input().strip()

            if responses == "CORRECT":
                continue


if __name__ == "__main__":
    solve()