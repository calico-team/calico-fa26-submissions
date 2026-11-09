import sys

def solve():
    input_line = sys.stdin.readline()
    if not input_line:
        return
    
    T = int(input_line.strip())
    
    for _ in range(T):
        line = sys.stdin.readline()
        while line and not line.strip():
            line = sys.stdin.readline()
        if not line:
            break
            
        parts = line.strip().split()
        N = int(parts[0])
        K = int(parts[1])
        
        chars = sys.stdin.readline().strip().split()
        
        known = [None] * N
        solved_count = 0
        is_solved = False
        
        for c_idx in range(K - 1):
            char_to_test = chars[c_idx]
            
            guess = []
            for i in range(N):
                if known[i] is not None:
                    guess.append(known[i])
                else:
                    guess.append(char_to_test)
            
            guess_str = "".join(guess)
            print(guess_str)
            sys.stdout.flush()
            
            response = sys.stdin.readline().strip()
            
            if response == "CORRECT":
                is_solved = True
                break
            
            for i in range(N):
                if known[i] is None and response[i] == char_to_test:
                    known[i] = char_to_test
                    solved_count += 1
            
            if solved_count == N:
                final_guess = "".join(known)
                print(final_guess)
                sys.stdout.flush()
                final_response = sys.stdin.readline().strip()
                is_solved = True
                break
        
        if not is_solved:
            last_char = chars[-1]
            for i in range(N):
                if known[i] is None:
                    known[i] = last_char
            
            final_guess = "".join(known)
            print(final_guess)
            sys.stdout.flush()
            response = sys.stdin.readline().strip()

if __name__ == '__main__':
    solve()