import sys

def solve(N,M,K,P):
    child = [[] for _ in range(N+1)]
    for i in range(N):
        child[P[i]].append(i+1)
    cnt = [0]*(N+1)
    stack = []
    for u in child[0]:
        stack.append((u,1))
    while stack:
        u,d = stack.pop()
        cnt[d] += 1
        for v in child[u]:
            stack.append((v,d+1))
    ans = min(N,M*K)
    total = 0
    for d in range(1,min(N,M)+1):
        total += cnt[d]
        ans = min(ans,total+(M-d+1)*K)
    return ans

def main():
    input = sys.stdin.buffer.readline
    T = int(input())
    for _ in range(T):
        N,M,K = map(int,input().split())
        P = list(map(int,input().split()))
        print(solve(N,M,K,P))

if __name__ == "__main__":
    main()