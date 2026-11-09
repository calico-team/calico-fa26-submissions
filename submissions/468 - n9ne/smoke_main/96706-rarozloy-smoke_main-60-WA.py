def solve(N, R, A):
    regen1=0-R
    regen2=0-R
    for i in A:
        if i>=regen1+R:
           regen1=i
        elif i>=max(regen1+2*R,regen2+R):
            regen2=i
        else: return "NO"
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
