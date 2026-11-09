import heapq

def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    """

    
    comesafter = [[] for _ in range(N)]

    requiredcourse = [0] * N

    for i in range(N):


        if P[i] != 0:

            alin = P[i] - 1



            comesafter[alin].append(i)

            requiredcourse[i] = 1

    
    subtree = [1] * N


    height = [1] * N

    sequence = []
    search = [i for i in range(N) if requiredcourse[i] == 0]

    while search:
        node = search.pop()

        sequence.append(node)

        for individual in comesafter[node]:



            search.append(individual)

    for node in reversed(sequence):


        for individual in comesafter[node]:

            subtree[node] += subtree[individual]



            height[node] = max(height[node], height[individual] + 1)

    
    available = []

    for i in range(N):
        
        if requiredcourse[i] == 0:


            heapq.heappush(
                available,
                (-subtree[i], -height[i], i)
            )

    completed = 0

    
    for _ in range(M):


        current_semester = []

       
        for _ in range(K):


            if not available:
                break

            _, _, node = heapq.heappop(available)


            current_semester.append(node)


            completed += 1

        
        for node in current_semester:


            for individual in comesafter[node]:


                heapq.heappush(


                    available,
                    (-subtree[individual], -height[individual], individual)
                )

    return completed


def main():
    T = int(input())

    for _ in range(T):
        N, M, K = map(int, input().split())
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))


if __name__ == '__main__':
    main()