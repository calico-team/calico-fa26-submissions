import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    num_test_cases = int(next(iterator))
    
    for _ in range(num_test_cases):
        N = int(next(iterator))
        K = int(next(iterator))
        alphabet = [next(iterator) for _ in range(K)]
        
        target = [''] * N
        
        # Query the first K - 1 characters
        for char in alphabet[:-1]:
            guess = char * N
            print(guess, flush=True)
            
            response = sys.stdin.readline().strip()
            if response == "CORRECT":
                break
            
            # Record matched positions
            for idx, c in enumerate(response):
                if c != '_':
                    target[idx] = c
        else:
            # Fill remaining unassigned positions with the last character
            last_char = alphabet[-1]
            for idx in range(N):
                if target[idx] == '':
                    target[idx] = last_char
            
            final_guess = "".join(target)
            print(final_guess, flush=True)
            
            response = sys.stdin.readline().strip()

if _name_ == "_main_":
    solve()
