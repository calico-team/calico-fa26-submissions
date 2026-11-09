def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    # YOUR CODE HERE
    A = []
    count = 0
    for i in range(N-1):
      A.append(int(str(len(str(E[i][0])))+(str(E[i][0])+str(E[i][1]))))
      count+=A[-1]
    A.append(count)
    return A


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    # YOUR CODE HERE
    temp = -1
    num = 0
    count = A[-1]
    E = []
    for i in range(len(A)-1):
      num = A[i]
      if num == -1:
        temp = i
        continue
      tS = str(num)
      tT = int(tS[0])
      E.append((int(tS[1:tT+1]),int(tS[tT+1:])))
      count-=num
    if(temp!=-1):
      A[temp] = count
      tS = str(count)
      tT = int(tS[0])
      E.append((int(tS[1:tT+1]),int(tS[tT+1:])))
    return E


def main():
    phase = input()
    N = int(input())
    if phase == 'FIRST':
        E = []
        for _ in range(N - 1):
            u, v = map(int, input().split())
            E.append((u, v))
        A = solve_phase1(N, E)
        print(' '.join(map(str, A)))
    else:
        A = list(map(int, input().split()))
        for u, v in solve_phase2(N, A):
            print(u, v)


if __name__ == '__main__':
    main()
