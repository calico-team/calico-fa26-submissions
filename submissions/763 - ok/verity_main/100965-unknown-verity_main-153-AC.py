import sys

input = sys.stdin.readline

T = int(input())

for _ in range(T):
    N, K = map(int, input().split())
    chars = input().split()

    ans = [None] * N

    for ch in chars:

       
        guess = ''.join(
            ans[i] if ans[i] is not None else ch
            for i in range(N)
        )

       
        print(guess, flush=True)

        response = input().strip()

        if response == "CORRECT":
            break

      
        for i in range(N):
            if response[i] != '_':
                ans[i] = response[i]