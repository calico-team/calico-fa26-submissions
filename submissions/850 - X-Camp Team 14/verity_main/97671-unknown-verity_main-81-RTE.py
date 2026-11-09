t = int(input())
for i in range(t):
    length_string, distinct_char = map(int, input().split())
    char = list(input().split())
    hint = ['_'] * length_string
    for j in char:
        ans = hint
        for i in range(length_string):
            if ans[i] == '_':
                ans[i] = j
        print(*ans, sep = '')
        hint = input()
        new_hint = []
        for i in hint:
            new_hint.append(i)
        hint = new_hint