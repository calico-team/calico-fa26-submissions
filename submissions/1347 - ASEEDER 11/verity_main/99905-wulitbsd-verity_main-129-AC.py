times = int(input())
for _ in range(times):
    N, K = map(int, input().split())
    lists = input().split()
    guess = [lists[0]] * N
    now = 1
    while True:
        print(''.join(guess), flush=True)
        feedback = input().strip()
        if feedback == 'CORRECT':
            break
        for i in range(N):
            if feedback[i] == '_':
                guess[i] = lists[now % K]
        now += 1