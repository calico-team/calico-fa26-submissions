import heapq
from collections import deque
def solve(N: int, M: int, K: int, P: list[int]) -> int:

    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    
    openlocks = [[] for _ in range(N +1)]

    waiting = [0] * (N + 1)

    alldepth = [1] * (N + 1)

    for idx in range(1, N + 1):

        if P[idx - 1] != 0:

            openlocks[P[idx - 1]].append(idx)

            waiting[P[idx - 1]] +=1

    line = deque()

    for idx in range(1, N +1):
        if waiting[idx] ==0:
            line.append(idx)

    while line:
        node = line.popleft()
        prefinal = P[node - 1]

        if prefinal !=0:
            alldepth[prefinal] = max(alldepth[prefinal],alldepth[node] +1)
            waiting[prefinal] -=1

            if waiting[prefinal] == 0:

                line.append(prefinal)

    open_listall =[]

    for n in range(1, N +1):
        if P[n - 1] == 0:
            heapq.heappush(open_listall,(-alldepth[n], n))

    allsum =0

    for _ in range(M):

        picked =[]

        for _ in range(K):
            if not open_listall:

                break

            _, course = heapq.heappop(open_listall)
            picked.append(course)
            allsum +=1

        for course in picked:
            for nxt in openlocks[course]:
                heapq.heappush(open_listall,(-alldepth[nxt], nxt))

        if not open_listall:
            break

    return allsum 

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()