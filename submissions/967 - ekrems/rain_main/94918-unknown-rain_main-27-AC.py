import sys
import bisect

input = sys.stdin.readline

def solve(N: int, K: int, L: list):
    dogu = {}
    kuzey = {}
    
    for x, y, z, d in L:
        toplam = x + y
        if d == 'E':
            if toplam not in dogu:
                dogu[toplam] = []
            dogu[toplam].append(x)
        else:
            if toplam not in kuzey:
                kuzey[toplam] = []
            kuzey[toplam].append(x)

    kayip = 0
    for toplam in dogu:
        if toplam in kuzey:
            k_list = kuzey[toplam]
            k_list.sort()
            for x in dogu[toplam]:
                sol = bisect.bisect_left(k_list, x + 1)
                sag = bisect.bisect_right(k_list, x + K - 1)
                kayip += (sag - sol)
                
    cevap = N * K - kayip
    return cevap

def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append((int(X), int(Y), int(Z), D))

        print(solve(N, K, L))

if __name__ == '__main__':
    main()