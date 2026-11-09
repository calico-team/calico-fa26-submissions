t = int(input())
otpt = []

for i in range(t):
    n = "YES"
    lst = input().split(" ")
    R = int(lst[-1])
    N = int(lst[0])
    L = input().split(" ")
    for i in range(N//3):
        L.remove(L[0])
        if (int(L[1]) - int(L[0])) < R:
            n = "NO"



    otpt.append(n)

for i in range(len(otpt)):
    print(otpt[i])

