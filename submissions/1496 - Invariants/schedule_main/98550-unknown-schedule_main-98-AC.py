import heapq
def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """ 
    lect = [[] for _ in range(N + 1)]
    for course in range(1, N + 1):
        lect[P[course - 1]].append(course)
    
    order = list(lect[0])
    for u in order:
        order.extend(lect[u])
    height = [1] * (N + 1)
    for u in reversed(order):
        for c in lect[u]:
            if height[c] + 1 > height[u]:
                height[u] = height[c] + 1
    
    avlb = [(-height[c], c) for c in lect[0]]
    heapq.heapify(avlb)
    taken = 0
    for _ in range(M):
        if not avlb:
            break
        unlocked = []
        for _ in range(min(K, len(avlb))):
            _, u = heapq.heappop(avlb)
            taken += 1
            unlocked.extend(lect[u])
        for c in unlocked:
            heapq.heappush(avlb, (-height[c], c))
    return taken

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()