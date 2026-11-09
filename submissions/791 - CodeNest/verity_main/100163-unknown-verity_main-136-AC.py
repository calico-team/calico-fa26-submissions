import sys

def solve():

    line = sys.stdin.readline()
    if not line:
        return
    T = int(line.strip())
    
    for _ in range(T):
   
        n_k_line = sys.stdin.readline().strip().split()
        N = int(n_k_line[0])
        K = int(n_k_line[1])
        
       
        chars_line = sys.stdin.readline().strip().replace(" ", "")
        chars = list(chars_line)
        
       
        known = ["?"] * N
        
        for c in chars:
            
            guess_list = []
            for i in range(N):
                if known[i] != "?":
                    guess_list.append(known[i])
                else:
                    guess_list.append(c)
            
            guess = "".join(guess_list)
            
           
            print(guess, flush=True)
            
           
            response = sys.stdin.readline().strip()
            
        
            if response == "CORRECT":
                break
     
            for i in range(N):
                if response[i] != '_':
                    known[i] = response[i]

if __name__ == '__main__':
    solve()