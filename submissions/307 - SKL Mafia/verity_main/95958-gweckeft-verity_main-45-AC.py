T = int(input()) 

def solve():
    N,K = tuple(map(int,input().split()))
    chars = input().split()
    tests = [letter*N for letter in chars]
    responses = []
    for test in tests:
        print(test,flush=True)
        response = input()
        if response == "CORRECT":
            return 
        responses.append(response)
    answer = [""] * N
    for response in responses:
        for i in range(N):
            if response[i] != "_":
                answer[i] = response[i] 
    print("".join(answer))
    feedback = input()
for _ in range(T):
    solve()