def solve(N: int, L: list[int], R: list[int]) -> int:
    """
    Returns the maximum possible value of X, Big Ben's matcha enjoyment.

    N: the days in Big Ben's life
    L: the lower bound of enjoyment from each store 
    R: the upper bound of enjoyment from each store
    """
    # YOUR CODE HERE
    current_xor = 0
    has_flexibility = False
    
    for i in range(N):
        current_xor ^= L[i]
        if L[i] < R[i]:
            has_flexibility = True
            
    
    
    if not has_flexibility:
        return current_xor
        
    
    
    answer = 0
    for bit in range(29, -1, -1):
        answer |= (1 << bit)
        
    
    return answer if has_flexibility else current_xor
    
    
    
def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))

if __name__ == '__main__':
    main()
