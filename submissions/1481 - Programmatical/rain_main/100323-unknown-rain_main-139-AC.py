a = int(input())


for i in range(a):

    b = input().split()

    n = int(b[0])

    k = int(b[1])


    d = {}
    for j in range(n):
        plane = input().split()

        xy = int(plane[0]) + int(plane[1])
        if xy not in d:
            d[xy] = [ (int(plane[0]) ,int(plane[1]),plane[-1])]
            #x y E/N
        else:
            d[xy].append( (int(plane[0]) ,int(plane[1]),plane[-1]) )
    counter = 0
    for group in d:
        subEE = []
        subNN = []

        for c in d[group]:
            if c[-1] == 'E':
                subEE.append(c[0])
            else:
                subNN.append(c[0])

        
        for e in subEE:

            for nn in subNN:

                if nn in range(e+1,e+k):
                    counter += 1
    print(n*k-counter)
            







        
        
