
t = int(input())

for i in range(t):
    n, m = map(int, input().split())
    chars = []
    correct = []
    for i in input().split():
        chars.append(i)
        
    for i in range(n):
        correct.append(chars[-1]);
    
    works = False
    for i in range(m - 1):
        print(chars[i] * n)
        
        ret = input()
        if (ret == "CORRECT"):
            works = True
            break
        idx = 0
        for c in ret:
            if c != "_":
                correct[idx] = c
            
            idx += 1
    if not works:
        print("".join(correct))
        input()