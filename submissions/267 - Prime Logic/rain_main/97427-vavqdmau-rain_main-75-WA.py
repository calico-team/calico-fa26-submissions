import sys

def solve(N:int,K: int, L:list):

    drones = []
    for x, y, _, direction in L:
        drones.append((y-x, x, direction))
    drones.sort()
    total = N*K
    left = 0
    east_count = 0
    for right,(diagonal, x, direction) in enumerate(drones):
        while left < right:
            prev_diagonal,prev_x,prev_direction = drones[left]
            if prev_diagonal == diagonal and x-prev_x < K:
                break
            if prev_direction == "E":
                east_count -= 1
            left += 1

        if direction == "E":
            east_count += 1
        else:

            total -= east_count
    return total



def main():


    input = sys.stdin.readline
    T = int(input())
    
    for _ in range(T):
        N,K = map(int, input().split())
        L = []
        for _ in range(N):
            x,y, z, direction = input().split()
            L.append((int(x), int(y), int(z), direction))

        print(solve(N, K, L))



if __name__ == "__main__":
    main()