def solve():
    N, R = map(int, input().split())

    smokes = 2
    requests = input().split()

    for i in range(len(requests)):
        try:
            if(int(requests[i+3]) - int(requests[i]) < 2*R):
                return False
        except IndexError:
            return True


T = int(input())
for i in range(T):
    if solve():
        print("YES")
    else:
        print("NO")
