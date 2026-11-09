n=int(input())
for i in range(n):
    a,b=map(int,input().split())
    string=input()
    time=string.split()
    count=0
    judge='T'
    for x in range(a):
        if x==0:
            if int(time[0])<count+b:
                judge='F'
        elif int(time[x])<int(time[x-1])+b:
            judge='F'
    if judge=='T':
        print('YES')
    else:
        print('NO')
            
    
