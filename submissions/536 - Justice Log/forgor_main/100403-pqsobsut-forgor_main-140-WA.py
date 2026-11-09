def solve_phase1(N: int, E: list[tuple[int, int]]) -> list[int]:
    """
    Output a list of N integers A_1 .. A_N

    N: the number of vertices
    E: the N - 1 edges of the tree as (u, v) pairs
    """
    # YOUR CODE HERE
    graph = []
    for i in range(N + 1):
        graph.append([])

    for start, end in E:
        graph[start].append(end)
        graph[end].append(start)

    parent_of = []
    for i in range(N + 1):
        parent_of.append(0)

    queue = [1]
    parent_of[1] = -1
    front = 0
    while front < len(queue):
        current = queue[front]
        front = front + 1
        for neighbor in graph[current]:
            if parent_of[neighbor] == 0:
                parent_of[neighbor] = current
                queue.append(neighbor)

    answer = []
    for i in range(N):
        answer.append(0)

    checksum = 0
    for vertex in range(2, N + 1):
        answer[vertex - 1] = parent_of[vertex]
        checksum = checksum + parent_of[vertex]

    answer[0] = checksum
    return answer


def solve_phase2(N: int, A: list[int]) -> list[tuple[int, int]]:
    """
    Output the N - 1 edges of the original tree as (u, v) pairs

    N: the number of vertices
    A: the N integers A_1 .. A_N with one value replaced with -1
    """
    # YOUR CODE HERE
    missing_index = -1
    for i in range(N):
        if A[i] == -1:
            missing_index = i
            break

    answer = []

    if missing_index == 0:
        for vertex in range(2, N + 1):
            answer.append((vertex, A[vertex - 1]))
        return answer

    checksum = A[0]
    known_sum = 0
    for vertex in range(2, N + 1):
        if vertex - 1 != missing_index:
            known_sum = known_sum + A[vertex - 1]

    missing_parent = checksum - known_sum

    for vertex in range(2, N + 1):
        if vertex - 1 == missing_index:
            answer.append((vertex, missing_parent))
        else:
            answer.append((vertex, A[vertex - 1]))

    return answer



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
