"""
*Return an N by M grid displaying the reading of the block seismometers after all earthquakes occur.
*
*N: number of rows in the grid
*M: number of columns in the grid
*Q: number of earthquakes
*earthquakes: a list of tuples (X, Y, P), where:
*    X: column of the epicenter
*    Y: row of the epicenter
*    P: power of the earthquake
"""
import math

def solve(N, M, Q, earthquakes):
    # YOUR CODE HERE
    # ok so i think we go backwards?? last quake wins
    grid=[0]*(N*M)
    nxt = list(range(N*M+1))
    rowleft=[M]*N
    total = N*M
    stuff={}
    #print("start")

    for i in range(Q-1,-1,-1):
        if total==0:
            break
        a=earthquakes[i][0]   # row
        b = earthquakes[i][1] # col
        p=earthquakes[i][2]
        pp=p*p

        if p not in stuff:
            tmp=[]
            w=p
            for d in range(p+1):
                while w*w+d*d>pp:
                    w=w-1
                tmp.append(w)
            stuff[p]=tmp
        tmp=stuff[p]

        for r in range(a-p,a+p+1):
            if rowleft[r]==0:
                continue
            d=r-a
            if d<0:
                d=-d
            w=tmp[d]
            start=r*M
            end=start+b+w
            x=start+b-w
            #print(r,x,end)

            while True:
                while nxt[x]!=x:
                    nxt[x]=nxt[nxt[x]]
                    x=nxt[x]
                if x>end:
                    break
                dc=x-start-b
                grid[x]=pp-d*d-dc*dc+1
                nxt[x]=x+1
                rowleft[r]=rowleft[r]-1
                total=total-1
                x=x+1

    res=[]
    for r in range(N):
        res.append(grid[r*M:(r+1)*M])
    return res

def main():
    T = int(input())
    for _ in range(T):
        N, M, Q = map(int, input().split())
        earthquakes = []
        for i in range(Q):
            X, Y, P = map(int, input().split())
            earthquakes.append((X, Y, P))
        answer = solve(N, M, Q, earthquakes)
        for row in answer:
            print(' '.join(map(str, row)))

if __name__ == '__main__':
    main()