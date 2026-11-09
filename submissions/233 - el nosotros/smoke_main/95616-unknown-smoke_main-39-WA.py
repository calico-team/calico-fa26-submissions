from itertools import pairwise

def solve(N: int, R: int, A: list) -> int:
    """
    
    N: Number of rows of the board
    R: Number of columns of the board
    A: Number of pieces
    """
    C = 1
    # YOUR CODE HERE
    for A1, A2 in pairwise(A):
        C += -1 + (A2 - A1)/R
        C = max(C, 2)
        if C < 0:
            return "NO"
    return "YES"


def main():
    T = int(input())
    for _ in range(T):
        temp = input().split()
        N, R = int(temp[0]), int(temp[1])
        A = [int(x) for x in input().split()]
        print(solve(N,R,A))

if __name__ == '__main__':
    main()
