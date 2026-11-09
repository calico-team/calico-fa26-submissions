def solve(N, K, A):
    rey=[""]*N
    ran=list(range(N))

    for bib in A:
        hab=rey[:]
        for kir in ran:
            hab[kir]=bib
        print_guess("".join(hab))

        yan=read_string()
        if yan=="CORRECT":
            break
        for kir in ran:
            if yan[kir]!="_":
                rey[kir]=yan[kir]

        ran=[kir for kir in ran if yan[kir]=="_"]
def read_string():
    return input()
def print_guess(guess):
    print(guess, flush=True)
def main():
    T=int(input())
    for _ in range(T):
        N,K=map(int, input().split())
        A=input().split()
        solve (N,K,A)
if __name__=="__main__":
    main()
        
