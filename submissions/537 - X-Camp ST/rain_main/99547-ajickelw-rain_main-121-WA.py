def solve(n: int, k: int, l: list):
    total = 0        
    visited = []
    for i in range(k):
        if i == 0:
            for j in range(len(l)):
                x, y = l[j][0], l[j][1]
                if [x, y] not in visited:
                    visited.append([x, y])


        else:
            for j in range(len(l)):
                if l[j][3] == 'N':                
                    x, y = l[j][0], l[j][1]

                    if [x, y] in visited:
                        visited.remove([x, y])
                    y += 1
                    if [x, y] not in visited:
                        visited.append([x, y])

                else:                    
                    x, y = l[j][0], l[j][1]

                    if [x, y] in visited:
                        visited.remove([x, y])
                    x += 1
                    if [x, y] not in visited:
                        visited.append([x, y])
                    
        total += len(visited)

        print(visited)
        print(total)

    return total


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