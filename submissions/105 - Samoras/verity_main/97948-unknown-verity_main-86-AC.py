import sys

def solve():
    read=sys.stdin.readline
    tests=int(read())

    for test in range(tests):
        line=read()
        while not line.strip():
            line=read()

        n,k=map(int,line.split())
        chars=read().split()
        known=["?"]*n
        solved=False

        for c in chars:
            print(c*n,flush=True)
            response=read().strip()
            if response=="CORRECT":
                solved=True
                break
            for i,ch in enumerate(response):
                if ch!="_":
                    known[i]=ch

        if not solved:
            print("".join(known),flush=True)
            response=read().strip()

if __name__=="__main__":
    solve()
