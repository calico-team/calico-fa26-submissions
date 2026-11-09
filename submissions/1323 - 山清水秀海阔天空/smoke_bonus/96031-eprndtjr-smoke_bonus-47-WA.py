t = int(input(''))
statement = []
stt = []
for i in range(t):
    n = input('')
    np = n.split(' ')
    r = input('')
    rp = r.split(' ')
    nn = int(np[0])
    n1 = int(np[1])
    for j in range(nn):
        if j == 0 and int(rp[j]) - n1 >= 0:
            statement.append(True)
        elif int(rp[j]) - n1 >= int(rp[j]) - int(rp[j-1]):
            statement.append(True)
        else:
            statement.append(False)
    if False in statement:
        stt.append(False)
    else:
        stt.append(True)
    statement = ['']

for k in stt:
    if k == False:
        print('NO')
    else:
        print('YES')
