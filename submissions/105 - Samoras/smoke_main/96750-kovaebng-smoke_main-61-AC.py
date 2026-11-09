import sys
def can_smoke_all(n,r,times):
    charges=2
    pending=0
    finish=0
    for t in times:
        while pending>0 and finish<=t:
            charges+=1
            pending-=1
            if pending>0:
                finish+=r
        if charges==0:
            return False
        charges-=1
        pending+=1
        if pending==1:
            finish=t+r
    return True

def main():
    data=list(map(int,sys.stdin.buffer.read().split()))
    if not data:
        return
    it=iter(data)
    T=next(it)
    answers=[]
    for _ in range(T):
        n=next(it)
        r=next(it)
        times=[next(it) for _ in range(n)]
        answers.append("YES" if can_smoke_all(n,r,times) else "NO")
    sys.stdout.write("\n".join(answers))

if __name__=="__main__":
    main()
