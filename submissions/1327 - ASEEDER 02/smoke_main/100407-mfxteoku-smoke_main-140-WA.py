def solve(N, R, A):
    """
    Output whether all of the requests can be fulfilled.

    N: Number of smoke requests
    R: Number of seconds needed for a smoke charge to recharge
    A: List of timestamps where smokes are requested
    """
    # YOUR CODE HERE
    smokec=0
    flag=1
    
    cn=A[1]-A[0]
    if cn>=R:
        smokec=1
        cn-=R
    for i in range(2,len(A)):

        if A[i]-A[i-1]+cn<R and smokec==0:
            flag=0
            break
        if A[i]-A[i-1]+cn<R and smokec>0:
            flag=1
            smokec-=1
            cn=A[i]-A[i-1]+cn
        if A[i]-A[i-1]+cn==R:
            flag=1
        if A[i]-A[i-1]+cn>R and smokec>0:
            flag=1
            smokec-=1
        if A[i]-A[i-1]+cn>R and smokec==0:
            flag=1
            cn=cn-R
            a=int(cn/R)
            if a<=2:
                smokec+=a
                cn-=a*R
            else:
                smokec=2
                cn-=2*R
           
                
                
    
    if flag ==1:
        print("YES")
    else:
        print("NO")
    
    
    
    return ""


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
