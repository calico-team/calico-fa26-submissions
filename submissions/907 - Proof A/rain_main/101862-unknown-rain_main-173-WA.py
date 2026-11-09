from collections import defaultdict

def do():
    n, k = map(int, input().split())
    X = []
    Y = []
    Z = []
    D = []
    things_on = defaultdict(list)
    for i in range(n):
        x, y, z, d = input().split()
        X.append(int(x))
        Y.append(int(y))
        Z.append(int(z))
        D.append(d)
        things_on[int(x)+int(y)].append(i)
    ans = k*n
    # print(ans, "AAA")
    kys = list(things_on.keys())
    for row in kys:
        # print(row, things_on[row])
        ln = len(things_on[row])
        # suffix_N = [0]*ln
        prefix_E = [0]*ln
        for i in range(ln):
            if D[things_on[row][i]] == "E":
                prefix_E[i] += 1
            if i != ln-1:
                prefix_E[i+1] += prefix_E[i]
        ptr = 0
        for i in range(ln):
            while X[things_on[row][i]]-X[ptr] > k-1 and ptr < i:
                ptr += 1
            if D[things_on[row][i]] == "N":
                # intersects all up to here
                # print(things_on[row][i], prefix_E[i], ptr)
                if ptr > 0:
                    ans -= (prefix_E[i] - prefix_E[ptr-1])
                else:
                    ans -= prefix_E[i]
    print(ans)
t = int(input())
for i in range(t):
    do()



    