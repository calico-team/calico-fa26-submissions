import sys

def solve():
    # Read T (number of test cases)
    t = int(input().strip())
    
    for _ in range(t):
        # Read N and K
        n, k = map(int, input().split())
        
        # Read the allowed characters
        allowed_chars = input().split()
        
        # Create a guess list. We'll initialize with the first allowed character.
        current_guess = [allowed_chars[0]] * n
        
        # We can make at most 100 guesses per test case
        for _ in range(100):
            # Output the current guess
            guess_str = "".join(current_guess)
            print(guess_str)
            sys.stdout.flush() # Flush is crucial for interactive problems
            
            # Read the judge's response
            response = input().strip()
            
            # If we guessed correctly, move to the next test case
            if response == "CORRECT":
                break
                
            # Otherwise, update our guess based on the response
            # The response will have underscores for incorrect positions,
            # and the correct characters for positions we guessed right.
            # In the next guess, we will fix the first incorrect position.
            for i in range(n):
                if response[i] != '_':
                    current_guess[i] = response[i]
                elif current_guess[i] == allowed_chars[0]:
                    # If this position is still wrong and we are using our default char,
                    # let's try the next character in the allowed list.
                    # We only want to change one position at a time to be efficient.
                    # So, we find the index of the current char and move to the next one.
                    idx = allowed_chars.index(current_guess[i])
                    if idx + 1 < k:
                        current_guess[i] = allowed_chars[idx + 1]
                    # Break after changing one character to keep the changes minimal.
                    break

if __name__ == "__main__":
    solve()