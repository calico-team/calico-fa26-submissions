import sys

def solve():
    line = sys.stdin.readline()
    if not line:
        return
    T = int(line.strip())
    for _ in range(T):
        line = sys.stdin.readline()
        if not line:
            break
        parts = line.split()
        N = int(parts[0])
        K = int(parts[1])
        
        chars_line = sys.stdin.readline()
        chars = chars_line.split()
        
        hidden = ['_'] * N
        guessed_correctly = False
        
        for c in chars:
            guess = c * N
            print(guess)
            sys.stdout.flush()
            
            resp = sys.stdin.readline().strip()
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
            resp = sys.stdin.readline().strip()

if __name__ == '__main__':
    solve()