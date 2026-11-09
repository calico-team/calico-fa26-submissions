testcases = int(input())

def willCollide(a, b):
    global k
    if(a[0] < b[0] and b[0] - a[0] == a[1] - b[1] and b[1] < a[1] and a[1] - b[1] < k):
            return True
    return False

for test in range(testcases): 
    global k
    n, k = map(int, input().split())

    arr = []
    arrE = []
    arrN = []
    sub = 0
    for i in range(n):
        x, y, z, d = map(str, input().split())
        x = int(x)
        y = int(y)
        arr.append([x,y,d])
        if(d == 'E'):
            arrE.append([x,y,d])
        elif(d == 'N'):
            arrN.append([x,y,d])

    for a in arrE:
        for b in arrN:
            if(willCollide(a, b)): 
                sub += 1
    
    print(n*k - sub)

