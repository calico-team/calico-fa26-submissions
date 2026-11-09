def function():


    try:
        n, k = map(int, input().split())
        a = list(map(str, input().split()))

    except EOFError:
        return
    answer = ['_'] * n

    tried = [[] for _ in range(n)]
    while True:
        guess = []

        for i in range(n):
            if answer[i] != '_':
                guess.append(answer[i])
            else:
                for c in a:
                    if c not in tried[i]:
                        guess.append(c)
                        tried[i].append(c)
                        break
                        
        guess = ''.join(guess)

        print(guess)

        try:
            m = input().strip()
        except EOFError:
            return

        if m == "CORRECT":
            break


        for i in range(min(n, len(m))):
            if m[i] != '_':
                answer[i] = m[i]

t = int(input())
for i in range(t):
    function()
        
        
