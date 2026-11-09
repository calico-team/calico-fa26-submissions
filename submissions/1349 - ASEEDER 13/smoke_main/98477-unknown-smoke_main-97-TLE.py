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

def code(time, cd, group, diffrence):
    smoke = 2
    shoot = 0
    count_cd = 0
    time_table = []
    if_count = False
    ans = "YES"
    for i in range(0, group[len(group)-1] + 1):
        if i in group:
            time_table.append(True)
        else:
            time_table.append(False)
    for i in range(0, group[len(group)-1] + 1):
        if if_count:
            count_cd += 1
        if smoke < 2:
            if_count = True
        else:
            if_count = False
        if count_cd >= cd and smoke < 2:
            smoke += 1
            count_cd = 0
            if_count = False
        if time_table[i] == True:
            if smoke <= 0:
                ans = "NO"
                break
            smoke -= 1
            shoot += 1
            if_count = True
    print(ans)


for i in range(t):
    code(n[i], r[i], a[i], diff[i])



