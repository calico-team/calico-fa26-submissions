def classes():
    N,M,K=[int(a) for a in input().split()]
    preq=[int(a)-1 for a in input().split()]
    classes=list(range(N))
    taken=[]
    count=0
    for sem in range(M):
        recent_took=[]
        took=0
        for cls in classes:
            if took<K:
                if preq[cls] in taken:
                    recent_took.append(cls)
                    took=took+1
                if preq[cls]==-1:
                    recent_took.append(cls)
                    took=took+1
        taken.extend(recent_took)
        for class_took in recent_took:
            classes.remove(class_took)
        count=count+took
    print(count)
T=int(input())
for case in range(T):
    classes()
