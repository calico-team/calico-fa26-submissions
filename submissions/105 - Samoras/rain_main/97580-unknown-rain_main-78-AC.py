import sys
from bisect import bisect_left,bisect_right

def solve():
    data=sys.stdin.buffer.read().split()
    if not data:
        return
    it=iter(data)
    tests=int(next(it))
    answers=[]

    for test in range(tests):
        n=int(next(it))
        k=int(next(it))
        east={}
        north={}
        for i in range(n):
            x,y,z=map(int,[next(it),next(it),next(it)])
            direction=next(it)
            diagonal=x+y
            points=east if direction==b'E' else north
            points.setdefault(diagonal,[]).append(x)

        for diagonal in east:
            east[diagonal].sort()

        collisions=0

        for diagonal in north:
            east_points=east.get(diagonal,[])
            if not east_points:
                continue
            for x in north[diagonal]:
                low=x-k+1
                high=x
                start=bisect_left(east_points,low)
                end=bisect_right(east_points,high)
                collisions+=end-start

        answers.append(str(n*k-collisions))

    sys.stdout.write("\n".join(answers))

if __name__=="__main__":
    solve()
