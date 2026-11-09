import sys

def solve():
    input_data = sys.stdin.readline().split()
    if not input_data:
        return
    
    n = int(input_data[0])
    k = int(input_data[1])
    
    chars = sys.stdin.readline().split()
    
    known = [None] * n
    
    for char in chars:
        guess = []
        for i in range(n):
            if known[i] is not None:
                guess.append(known[i])
            else:
                guess.append(char)
        
        guess_str = "".join(guess)
        sys.stdout.write(guess_str + "\n")
        sys.stdout.flush()
        
        response = sys.stdin.readline().strip()
        
        if response == "CORRECT":
            return
            
        for i in range(n):
            if response[i] != '_':
                known[i] = response[i]

def main():
    t_str = sys.stdin.readline()
    if not t_str:
        return
    t = int(t_str.strip())
    for _ in range(t):
        solve()

if __name__ == "__main__":
    main()
