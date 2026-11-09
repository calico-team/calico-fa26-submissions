def merafunction(N,R,A):
    isl = 0
    kar = 0
    for tt in A:
        c1 = (tt >= isl)
        c2 = (tt <= kar)
        if not c1 and not c2:
            return "no"
        elif c1 and c2:
            isl = tt + R
            return isl
        elif c1 and not c2:
            c1 = kar + R
        elif not c1 and c2:
            kar = isl + R
    return "yes"
N=4
R=30
A =[20,30,40,50]
r= merafunction(N,R,A)
print(r)