def solve(n_n, r_r, a_a):
    paisy= 2
    dobara_paisay= 0

    for t_t in a_a:

        if paisy== 0:
            if t_t<      dobara_paisay:
                return  "NO"

            paisy= 1

        paisy     -= 1

        if paisy== 0:
            dobara_paisay +=     r_r
        else:
            dobara_paisay= t_t +      r_r

    return "YES"



def main():
    T = int(input())
    for _ in range(T):
        temp = input().split()
        n_n = int(temp[0])
        r_r = int(temp[1])
        a_a = list(map(int, input().split()))
        print(solve(n_n, r_r, a_a))


if __name__ == '__main__':
    main()
