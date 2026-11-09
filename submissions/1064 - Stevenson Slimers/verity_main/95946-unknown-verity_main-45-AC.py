t = int(input())
for i in range(t):
    n, k = map(int, input().split())
    letters = input().split()

    count = 0
    corrects = [""] * n
    
    while True:
        correct_indices = [letters[count] if x == "" else x for x in corrects]
        guess =  "".join(correct_indices)
        print(guess)
        answer = input()
        if (answer == "CORRECT"):
            break
        answer_split = list(answer)
        
        for i, ans in enumerate(answer_split):
            if (ans == letters[count]):
                corrects[i] = ans
        count += 1
    
