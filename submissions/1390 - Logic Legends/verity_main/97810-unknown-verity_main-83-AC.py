def solve(N, K, A):
    known = [None] * N
    for i in range(K):
        letter = A[i]
        guess = ''.join(known[j] if known[j] is not None else letter for j in range(N))
        print_guess(guess)
        resp = read_string().strip()
        if resp == 'CORRECT':
            return
        for j in range(N):
            if resp[j] != '_':
                known[j] = resp[j]
 
 
def read_string():
    s = input()
    return s
 
 
def print_guess(guess):
    print(guess, flush=True)
 
 
def main():
    T = int(input())
 
    for _ in range(T):
        N, K = map(int, input().split())
        A = input().split()
 
        solve(N, K, A)
 
 
if __name__ == '__main__':
    main()
 