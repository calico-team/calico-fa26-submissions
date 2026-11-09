import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    T = int(input_data[0])
    idx = 1
    
    for _ in range(T):
        N = int(input_data[idx])
        K = int(input_data[idx + 1])
        idx += 2
        
        allowed = []
        for _ in range(K):
            allowed.append(input_data[idx])
            idx += 1
            
        current_guess = [allowed[0]] * N
        
        print("".join(current_guess))
        sys.stdout.flush()
        
        response = sys.stdin.readline().strip()
        if response == "CORRECT":
            continue
            
        for i in range(N):
            if response[i] != '_':
                current_guess[i] = response[i]
                
        for i in range(N):
            if current_guess[i] == allowed[0] and response[i] == '_':
                for char in allowed[1:]:
                    current_guess[i] = char
                    print("".join(current_guess))
                    sys.stdout.flush()
                    
                    res = sys.stdin.readline().strip()
                    if res == "CORRECT":
                        break
                    if res[i] != '_':
                        break
                if res == "CORRECT":
                    break

if __name__ == '__main__':
    solve()