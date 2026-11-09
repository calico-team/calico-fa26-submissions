def solve(N, R, A):
    fst=0
    scnd=0
    for req in A:
        if fst<=req:
            fst=req+R
        elif scnd<=req:
            scnd=fst+R
        else:
            return "NO"
    else:
        return "YES"
    
        
        
    


def main():
    T = int(input())
    for _ in range(T):
        temp = input().split()
        N = int(temp[0])
        R = int(temp[1])
        A = list(map(int, input().split()))
        print(solve(N, R, A))


if __name__ == '__main__':
    main()
