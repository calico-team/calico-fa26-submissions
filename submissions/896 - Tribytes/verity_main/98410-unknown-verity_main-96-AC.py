tst_case = int(input())

for _ in range(tst_case):
    length, num_types = map(int, input().split())
    letters = input().split()

    answer = ['?'] * length

    for letter in letters:
        print(letter * length, flush=True)
        reply = input().strip()

        if reply == "CORRECT":
            break

        for pos in range(length):
            if reply[pos] != '_':
                answer[pos] = reply[pos]
    else:
        
        print(''.join(answer), flush=True)
        input()