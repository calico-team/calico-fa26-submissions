from collections import deque
from functools import cmp_to_key

graph = {}

def cmp(x , y):
    return len(graph[y]) - len(graph[x])

def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    global graph 
    graph = {}
    for i, e in enumerate(P):
        if i+1 not in graph:
            graph[i+1] = []
        if e not in graph:
            graph[e] = [i+1]
        else:
            graph[e].append(i+1)
    # print(graph)
    # BFS
    count = 0
    d = deque([])
    for x in graph[0]:
        d.append(x)
    for _ in range(M):
        iii = 0
        d.append("break")
        optionsToAdd = []
        while iii < K:
            if not len(d):
                return count
            curr = d.popleft()
            if curr == "break":
                if  iii != 0:
                    break
                else:
                    continue
            # print(curr)
            count += 1
            for x in graph[curr]:
                optionsToAdd.append(x)
            iii += 1
        sorted(optionsToAdd, key=cmp_to_key(cmp))
        for x in optionsToAdd:
            d.append(x)


    return count

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()