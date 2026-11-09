kk = int(input())
for i in range(kk):
    n, k = map(int,input().split())
    array = [[0]*4 for _ in range(n)]
    rain = 0
    for i in range(n):
        array[i] = (list(map(str,input().split())))
    for i in range(k):
        rainy = set()
        rainx = set()
        for j in range(n):
            x= int(array[j][0])
            y = int(array[j][1])
            z = int(array[j][2])
            d = array[j][3]
            if x not in rainx and y not in rainy:
                rain += 1
                rainx.add(x)
                rainy.add(y)
            if d == 'N':
                y += 1
            else:
                x += 1
            array[j][0] = str(x)
            array[j][1] = str(y)
    print(rain)   
        
        
        
        