import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    T = int(input_data[0])
    idx = 1
    for _ in range(T):
        N = int(input_data[idx])
        K = int(input_data[idx+1])
        idx += 2
        chars = []
        for _ in range(K):
            chars.append(input_data[idx])
            idx += 1
        
        hidden = ['_'] * N
        guessed_correctly = False
        
        for c in chars:
            guess = c * N
            print(guess)
            sys.stdout.flush()
            resp = input().strip()
            if resp == "CORRECT":
                guessed_correctly = True
                break
            for i in range(N):
                if resp[i] != '_':
                    hidden[i] = resp[i]
        
        if not guessed_correctly:
            final_guess = "".join(hidden)
            print(final_guess)
            sys.stdout.flush()
            resp = input().strip()

if __name__ == '__main__':
    solve()