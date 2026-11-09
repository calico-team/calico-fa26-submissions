# --- YOUR CORRECTED SOLVE FUNCTION ---
def solve(N: int, K: int, A: list[str]) -> None:
    new_known = ['_'] * N

    for i in range(K-1):
        current_guess = A[i]*N
        print_guess(current_guess)
        evaluate = read_string()

        if evaluate == "CORRECT":
            return

        for j in range(N):
            if evaluate[j] != '_':
                new_known[j] = evaluate[j]

    for z in range(N):
        if new_known[z] == '_':
            new_known[z] = A[-1]

    print_guess("".join(new_known))
    read_string()


def read_string():
    """Simulates the judge evaluating the guess and returning the feedback."""
    global last_guess, hidden_string
    
    if last_guess == hidden_string:
        print("  -> Judge responds: CORRECT\n")
        return "CORRECT"
        
    response = ""
    for i in range(len(hidden_string)):
        if last_guess[i] == hidden_string[i]:
            response += last_guess[i]
        else:
            response += "_"
            
    print(f"  -> Judge responds: {response}")
    return response

def print_guess(guess):
    """Simulates sending the guess to the judge."""
    global last_guess, guess_count
    last_guess = guess
    guess_count += 1
    print(f"Guess {guess_count}: {guess}")

def run_test_case(test_name, target, n, k, allowed_chars):
    """Sets up a test case for the mock judge."""
    global hidden_string, guess_count
    print(f"--- RUNNING {test_name} ---")
    print(f"Target String: {target}, N={n}, K={k}, Allowed={allowed_chars}")
    
    hidden_string = target
    guess_count = 0
    
    solve(n, k, list(allowed_chars))
    print(f"Total guesses used: {guess_count} (Limit: 100)\n")

def main():
    # Test Case 1 from the image
    run_test_case(
        test_name="TEST CASE 1", 
        target="LFCV", 
        n=4, 
        k=4, 
        allowed_chars="LCFV"
    )

    # Test Case 2 from the image
    run_test_case(
        test_name="TEST CASE 2", 
        target="ECABEEACDA", 
        n=10, 
        k=5, 
        allowed_chars="ABCDE"
    )

if __name__ == '__main__':
    main()