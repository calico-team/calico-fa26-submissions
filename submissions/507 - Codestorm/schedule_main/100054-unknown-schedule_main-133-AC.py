import heapq
def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    child= [[] for _ in range(N)]
    roots=[]

    for i, prq in enumerate(P):
        if prq==0:
            roots.append(i)
        else:
            child[prq -1].append(i)
    h=[1]*N
    order=[]
    stack=roots[:]

    while stack:
        i =stack.pop()
        order.append(i)
        stack.extend(child[i])
    for i in reversed(order):
        for j in child[i]:
            h[i] = max(h[i],1+h[j])
    available =[(-h[i],i) for i in roots]
    heapq.heapify(available)
    taken=0
    for _ in range(M):
        this_semester=[]
        for _ in range(min(K,len(available))):
            _, course = heapq.heappop(available)
            this_semester.append(course)
        taken +=len(this_semester)
        for i in this_semester:
            for j in child[i]:
                heapq.heappush(available,(-h[j],j))
    return taken


def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()