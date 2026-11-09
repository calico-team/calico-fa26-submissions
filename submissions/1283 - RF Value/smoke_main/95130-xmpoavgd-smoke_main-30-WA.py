t = int(input())
otpt = []
for i in range(t):
    n = "YES"
    lst = input().split(" ")
    R = int(lst[-1])
    N = int(lst[0])
    L = input().split(" ")
    for j in range(N-1):
        if (int(L[j+1]) - int(L[j])) < R:
            n = "NO"
        else:
            pass
    otpt.append(n)

for i in range(len(otpt)):
    print(otpt[i])

