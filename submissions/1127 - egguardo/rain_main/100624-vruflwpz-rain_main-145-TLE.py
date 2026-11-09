z = int(input())
ans = []
class Drone:
    def __init__(self,x,y,z,d):
        self.x= x
        self.y = y
        self.z = z
        self.d = d

    def pos(self):
        return (self.x,self.y)

drones = []



for y in range(z):

    num = 0
    drones = []

    d, n = input().split(' ')
    d = int(d)
    n = int(n)

    for i in range(d):

        x,y,z,dir = input().split(' ')
        x = int(x)
        y = int(y)
        z = int(z)

        drones.append(Drone(x,y,z,dir))

    for ni in range(n):

        passed = True
        for di in range(len(drones)):
            for i2 in range(len(drones)):
                if not di == i2:
                    if drones[di].pos() == drones[i2].pos():

                        passed = False
            
            if passed: num += 1

            if drones[di].d == 'N':
                drones[di].y += 1
            elif drones[di].d == 'E':
                drones[di].x += 1
            passed = True

    #print(num)
    ans.append(num)
    print(num)

ans = [str(i) for i in ans]
#print('\n'.join(ans))

"""
0 3 0 E
2 1 1 N
8 8 2 E

5 5
0 6 0 E
2 4 1 E
4 2 2 N
5 1 3 N
9 9 4 N

4 2
0 5 0 E
5 0 1 N
1 3 2 E
3 1 3 N

"""
