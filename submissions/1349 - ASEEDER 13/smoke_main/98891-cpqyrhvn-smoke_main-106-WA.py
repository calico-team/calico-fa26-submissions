t = int(input())
a = []
nr = []
n = []
r = []
diff = []
for i in range(t):
    nr = input().split(" ")
    n.append(int(nr[0]))
    r.append(int(nr[1]))
    a.append(input().split(" "))
    diff.append([])
for i in range(t):
    for j in range(n[i]):
        a[i][j] = int(a[i][j])
        if j > 0:
            diff[i].append(a[i][j]- a[i][j-1])
        else:
            diff[i].append(a[i][j])

def code(time, cd, df):
    time_table = 0
    smoke = 2
    left = 0
    ans = "YES"
    for i in range(time):
        time_table += df[i]
        smoke = min(2, smoke + (left + df[i]) // cd)
        left = (left + df[i]) % cd
        if smoke <= 0:
            ans = "NO"
            break
        smoke -= 1
    print(ans)

for i in range(t):
    code(n[i], r[i], diff[i])



