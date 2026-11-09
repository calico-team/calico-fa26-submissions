def solve(N, R, A):
    a=2
    list1=[]
    for i in A:
        while list1 and list1[0]<=i:
            list1.pop(0)
            a=a+1
        if a==0:
            return 'NO'
        a=a-1
        if list1:
            list2=list1[-1]+R
        else:
            list2=i+R
        list1.append(list2)
            
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
