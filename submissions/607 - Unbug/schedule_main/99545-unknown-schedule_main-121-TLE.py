def solve(N, M, K, P):
    unlocks = [[] for _ in range(N + 1)]
    ready = []
    
    for course_id in range(1, N + 1):
        prereq = P[course_id - 1]
        if prereq == 0:
            ready.append(course_id)
        else:
            unlocks[prereq].append(course_id)

    priority = [0] * (N + 1)
    
    changed = True
    while changed:
        changed = False
        for course_id in range(1, N + 1):
            prereq = P[course_id - 1]
            if prereq != 0 and priority[prereq] < priority[course_id] + 1:
                priority[prereq] = priority[course_id] + 1
                changed = True

    total_classes_taken = 0

    for _ in range(M):
        if not ready:
            break

        ready.sort(key=lambda c: priority[c], reverse=True)

        classes_taken = ready[:K]
        ready = ready[K:]

        total_classes_taken += len(classes_taken)

        for course_id in classes_taken:
            for next_course in unlocks[course_id]:
                ready.append(next_course)

    return total_classes_taken


def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()