from collections import defaultdict
from bisect import bisect_left, bisect_right
def solve(N,K,L):
    rey=defaultdict(list)
    hab=defaultdict(list)
    for X,Y,Z,D in L:
        yan=X+Y
        if D=="E":
            rey[yan].append(X)
        else:
            hab[yan].append(X)
    kir=0
    for yan in rey:
        if yan not in hab:
            continue
        bib=sorted(hab[yan])
        for ran in rey[yan]:
            kir+=bisect_right(bib,ran+K-1)-bisect_left(bib,ran)
    return N*K-kir
def main():
    T=int(input())
    for _ in range(T):
        N,K=map(int,input().split())
        L=[]
        for _ in range(N):
            X,Y,Z,D=input().split()
            L.append((int(X),int(Y),int(Z),D))
        print(solve(N,K,L))
if __name__=="__main__":
    main()