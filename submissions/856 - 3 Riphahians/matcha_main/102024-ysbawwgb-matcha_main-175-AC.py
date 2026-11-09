import sys

def solve():
    input=sys.stdin.buffer.readline
    quantity=int(input())
    for i in range(quantity):
        n=int(input())
        l=list(map(int,input().split()))
        r=list(map(int,input().split()))
        if n==1:
            print(r[0])
            continue
        a=[None]*30
        ans=0
        for i in range(n):
            ans=add(l[i],r[i],a,ans)
        for bit in range(29,-1,-1):
            if a[bit] is None:
                continue
            x,y=a[bit]
            a[bit]=None
            mask=(1<<bit)-1
            if ans>>bit&1:
                ans=add(mask-x,mask,a,ans)
            else:
                ans=add(0,y,a,ans^(1<<bit))
        print(ans)

def best(x,y):
    return (x^y)|((1<<(x&y).bit_length())-1)

def add(l,r,a,ans):
    if l==r:
        return ans^l
    bit=(l^r).bit_length()-1
    mask=(1<<bit)-1
    ans^=(l>>(bit+1))<<(bit+1)
    x=mask-(l&mask)
    y=r&mask
    if a[bit] is None:
        a[bit]=(x,y)
    else:
        u,v=a[bit]
        a[bit]=(max(best(x,u),best(y,v)),max(best(x,v),best(y,u)))
        ans^=mask
    return ans

solve()