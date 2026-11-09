def solve(N, R, A):
    o_c = 2          
    n_r = None    

    for t in A:
        while n_r is not None and n_r <= t:
            o_c += 1
            if o_c < 2:
                n_r += R      
            else:
                n_r = None    

        if o_c == 0:
            return "NO"

        o_c -= 1
        if n_r is None:
            n_r = t + R

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
