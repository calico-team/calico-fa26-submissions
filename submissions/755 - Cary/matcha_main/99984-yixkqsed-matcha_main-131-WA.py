numeroftestcases=int(input())
l=[]
r=[]
f=[]
days=0
ans=[]
a=[]
b=[]
c=0
d=0
for i in range(numeroftestcases):
    # days=int(input())
    # print("hi")
    c=0
    b=[]
    a=[]
    d=0
    e=0
    f=True
    daysi=input()
    days=input()
    l=days.split()
    days=input()
    r=days.split()
    for j in range(len(l)):
        l[j]=int(l[j])
    for j in range(len(r)):
        r[j]=int(r[j])
    for j in range(len(r)-1):
        if not r[j]==r[j+1]:
            f=False
    if f:
        ans.append(r[0])
        continue
    for j in range(len(l)):
        c=0
        for k in range(l[j]+1,r[j]+1):

            a.append(k)

        for m in range(len(a)):
            c=c^a[m]
        b.append(c)
    for j in range(len(b)):
        d=max(d,b[j])
    print(a,b)
    # print(a,b,l,r)
    ans.append(d)

    # for j in range(days):
for i in range(len(ans)):
    print(ans[i])