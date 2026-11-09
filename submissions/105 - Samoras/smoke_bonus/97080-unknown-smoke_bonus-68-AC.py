import sys

def solve():
    data=sys.stdin.buffer.read().split()
    it=iter(data)
    tests=int(next(it))
    answers=[]
    for test in range(tests):
        n=int(next(it))
        recharge=int(next(it))
        charges=2
        pending=0
        finish=0
        possible=True
        for i in range(n):
            time=int(next(it))
            if possible:
                while pending>0 and finish<=time:
                    charges+=1
                    pending-=1
                    if pending>0:
                        finish+=recharge
                if charges==0:
                    possible=False
                else:
                    charges-=1
                    pending+=1
                    if pending==1:
                        finish=time+recharge
        answers.append("YES" if possible else "NO")
    sys.stdout.write("\n".join(answers))

if __name__=="__main__":
    solve()
