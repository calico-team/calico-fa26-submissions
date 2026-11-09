def amtWater(arr):
    loc = set()
    for tup in arr:
        loc.add(f'{tup[0]},{tup[1]}')
    return len(loc)

def move(arr):
    for tup in arr:
        if(tup[2] == 'E'):
            tup[0] += 1
        if(tup[2] == 'N'):
            tup[1] += 1

    return arr

testcases = int(input())

for test in range(testcases): 
    n, k = map(int, input().split())

    arr = []
    for i in range(n):
        x, y, z, d = map(str, input().split())
        x = int(x)
        y = int(y)
        arr.append([x,y,d])

    n = 0
    for i in range(k):
        n += amtWater(arr)
        arr = move(arr)
    
    print(n)


