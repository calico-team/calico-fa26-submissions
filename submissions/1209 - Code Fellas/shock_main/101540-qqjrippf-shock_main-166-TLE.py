def main():
    T=int(input())
    for _ in range (T):
        N,M,Q=map(int, input().split())
        rey=[[0]*M for _ in range (N)]
        for ran in range(Q):
            R,C,P=map(int, input().split())
            for yan in range(N):
                for bib in range(M):
                    hab=(yan-R)**2+(bib-C)**2
                    if hab<=P**2:
                        kir=P**2-hab+1
                        rey[yan][bib]=kir
        for row in rey:
            print(*row)
if __name__=="__main__":
    main()