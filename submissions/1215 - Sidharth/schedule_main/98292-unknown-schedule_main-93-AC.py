def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    # YOUR CODE HERE
    import heapq
    kids=[]
    for i in range(N+1):
        kids.append([])
    for i in range(1, N+1):
        pre=P[i-1]
        if pre != 0:
            kids[pre].append(i)
    
    order=[]
    for i in range(1, N+1):
        if P[i-1] == 0:
            order.append(i)

    spot=0
    while spot < len(order):
        current=order[spot]
        spot+=1
        
        for kid in kids[current]:
            order.append(kid)

    height=[1]* (N+1)
    for j in range(len(order)-1, -1,-1):
        node=order[j]
        pre = P[node-1]
        if pre!=0:
            if height[node] + 1 > height[pre]:
                height[pre] = height[node] + 1

    ready=[]
    for i in range(1, N+1):
        if P[i-1] == 0:
            heapq.heappush(ready, (-height[i], i))

    total=0

    for semester in range(M):
        if len(ready)==0:
            break

        taken = []
        count=0
        while count < K and len(ready) > 0:
            item = heapq.heappop(ready)
            taken.append(item[1])
            count+=1

        total+=len(taken)

        for node in taken:
            for kid in kids[node]:
                heapq.heappush(ready, (-height[kid], kid))

    return total 

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()