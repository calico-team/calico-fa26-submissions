from sys import stdout

def solve():
    n, k = [int(i) for i in input().split()]
    chars = input().split()
    # info
    ans = []
    for char in chars:
        print(char * n)
        stdout.flush()
        ans.append(input().strip())
        if ans[-1] == 'CORRECT':
            return
    
    str_ans = ['' for i in range(n)]
    for i in ans:
        for j in range(n):
            if i[j] != '_':
                str_ans[j] = i[j]

    print(''.join(str_ans))
    stdout.flush()
    input()

for i in range(int(input())):
    solve()