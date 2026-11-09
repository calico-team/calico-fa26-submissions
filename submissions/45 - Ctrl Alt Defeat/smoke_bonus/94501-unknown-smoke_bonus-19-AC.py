def input_string(): return input().rstrip()
def input_interable_float(sep = " "): return map(float, input_string().split(sep))

for _ in range(int(input().strip())):
    N, R = input_interable_float()
    num_charges = 2
    next_refill = -1
    for request in input_interable_float():
        while request >= next_refill and num_charges < 2:
            num_charges += 1
            next_refill += R
        if num_charges == 2:
            next_refill = request + R
        if num_charges <= 0:
            print("NO")
            break
        num_charges -= 1
    else:
        print("YES")

