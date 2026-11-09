
def solve(N: int, K: int, L: list):
    counter = 0
    for a in range(K):
        coordinates = set()
        for b in L:
            coordinates.add((b[0], b[1]))
        counter += len(coordinates)
        for b in L:
            if b[3]=="N":
                b[1]+=1
            else: 
                b[0]+=1
    return counter

def main():
    T = int(input())
    for _ in range(T):
        N, K = map(int, input().split())
        L = []
        for _ in range(N):
            X, Y, Z, D = input().split()
            L.append([int(X), int(Y), int(Z), D])

        print(solve(N, K, L))

if __name__ == '__main__':
    main()