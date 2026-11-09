def solve(N, R, A):
    my_smoke_charge_1 = 0
    my_smoke_charge_2 = 0
    my_answer = "YES"

    for time in A:
        if my_smoke_charge_1 <= time and my_smoke_charge_2 <= time:

            if my_smoke_charge_1 <= my_smoke_charge_2:
                my_smoke_charge_1 = time + R

            else:
                my_smoke_charge_2 = time + R
        elif my_smoke_charge_1 <= time:
            my_smoke_charge_1 = my_smoke_charge_2 + R

        elif my_smoke_charge_2 <= time:
            my_smoke_charge_2 = my_smoke_charge_1 + R
        else:
            my_answer = "NO"

            break

    return my_answer


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
