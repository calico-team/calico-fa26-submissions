import heapq

def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    # YOUR CODE HERE
    if N==2:
        return [0,0]

    neighbors=[]
    for i in range(N+1):
        neighbors.append([])

    edge_count = [0] * (N+1)
    for u,v in E:
        neighbors[u].append(v)
        neighbors[v].append(u)
        edge_count[u]+=1
        edge_count[v]+=1

    already_cut = [False] * (N+1)
    leaves=[]
    for i in range(1, N+1):
        if edge_count[i]==1:
            heapq.heappush(leaves,i)

    prufer_code=[]

    for step in range(N-2):
        leaf=heapq.heappop(leaves)
        already_cut[leaf] = True

        parent=0
        for candidate in neighbors[leaf]:
            if already_cut[candidate] == False:
                parent=candidate
        
        prufer_code.append(parent)
        edge_count[parent]-=1

        if edge_count[parent]==1:
            heapq.heappush(leaves, parent)

    total=0
    for p in prufer_code:
        total+=p
    total=total%1000000
    output_list=prufer_code
    output_list.append(total)
    output_list.append(0)
    return output_list

def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    # YOUR CODE HERE
    if N==2:
        return [(1, 2)]

    prufer = []
    for i in range(N-2):
        prufer.append(A[i])

    saved_sum=A[N-2]

    lost_index=-1
    for i in range(N-2):
        if prufer[i] == -1:
            lost_index = i

    if lost_index!=-1:
        others=0
        for i in range(N-2):
            if i != lost_index:
                others += prufer[i]
        
        prufer[lost_index] = (saved_sum - others) % 1000000

    deg = [1] * (N+1)
    for p in prufer:
        deg[p] += 1

    leaves=[]
    for i in range(1, N+1):
        if deg[i] == 1:
            heapq.heappush(leaves, i)
        
    tree_edges = []
    for p in prufer:
        leaf = heapq.heappop(leaves)
        tree_edges.append((leaf, p))
        deg[p] -= 1
        if deg[p] == 1:
            heapq.heappush(leaves,p)
    
    last_vertex1 = heapq.heappop(leaves)
    last_vertex2 = heapq.heappop(leaves)
    tree_edges.append((last_vertex1,last_vertex2))

    return tree_edges


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
