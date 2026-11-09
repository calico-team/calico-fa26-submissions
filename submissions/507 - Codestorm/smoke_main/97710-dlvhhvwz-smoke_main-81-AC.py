def solve(N, R, A):
    charges=2
    pending=0
    recharge=0
    for i in A:
        while pending>0 and recharge<=i:
            charges +=1
            pending -=1
            recharge +=R
        if charges ==0:
            return "NO"
        if pending==0:
            recharge =i+R
        pending +=1
        charges -=1
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
