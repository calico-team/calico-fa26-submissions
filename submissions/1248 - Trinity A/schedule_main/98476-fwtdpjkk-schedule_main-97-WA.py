def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.

    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    # YOUR CODE HERE
    total = 0
    # class number, classes relying on, prereqs for class
    # What's the idea?
    # The idea is so take the classes and from there find the classes with the least prereqs
    # of those classes we then want to first take those that unlock the most possible classes in the next semester
    classes = [[i+1, [], P[i]] for i in range(N)]
    for i, prereq in enumerate(P):
        classes[prereq-1][1].append(i+1)

    for i in range(M):
        if classes == []: break
        classes.sort(key=lambda x: (x[2], len(x[1])))
        to_remove = []
        for j in range(K):
            if classes[0][2] != 0: break
            to_remove.append(classes[0])
            classes.pop(0)
            total += 1

        for removed in to_remove:
            for prereq in removed[1]:
                for k in range(len(classes)):
                    if classes[k][0] == prereq: classes[k][2] = 0



    return total

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()
