def solve(N: int, M: int, K: int, P: list[int]) -> int:
    """
    Return the maximum number of classes that can be taken across M semesters.
    
    N: the number of classes
    M: the number of semesters
    K: the maximum number of classes you can take per semester
    P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
    """
    eligible={a : [] for a in range(1, N+1)}
    todo=[]
    
    for i in range(1, N+1):
        pre=P[i-1]
        if pre!=0:
            eligible[pre].append(i)
        else:
            todo.append(i)
    length={}
    def get_len(i):
        if i not in length:
            length[i]=max((get_len(x) for x in eligible[i]), default=0)
        return length[i]
        
    for y in range(1,N+1):
        get_len(y)
        
    total=0   
        
    for x in range(M):
        if not todo:
            break
        
        now=todo[:K]
        todo=todo[K:]
        total+=len(now)
        
        for check in now:
            todo.extend(eligible[check])
        
    return total

def main():
    T = int(input())
    for _ in range(T):
        N, M, K = list(map(int, input().split()))
        P = list(map(int, input().split()))
        print(solve(N, M, K, P))

if __name__ == '__main__':
    main()