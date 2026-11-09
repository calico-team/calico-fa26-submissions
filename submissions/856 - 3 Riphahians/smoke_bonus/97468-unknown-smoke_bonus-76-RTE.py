import sys

def solve():
    input=sys.stdin.buffer.readline
    quantity=int(input())
    for i in range(quantity):
        n,r=map(int,input().split())
        a=map(int,input().split())
        count = 2
        time = 0
        can_use = True
        for x in a:
            while count<2 and time<=x:
                count+=1
                time+=r
            if count==0:
                can_use=False
                break
            if count==2:
                time=x+r
            count-=1
        if can_use == True:
            print("YES")
        else:
            print("NO")

solve()
