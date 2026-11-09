def solve(N: int, L: list[int], R: list[int]) -> int:
    """
    Returns the maximum possible value of X, Big Ben's matcha enjoyment.

    N: the days in Big Ben's life
    L: the lower bound of enjoyment from each store 
    R: the upper bound of enjoyment from each store
    """
    # YOUR CODE HERE
import sys

def solve(N: int, L: list[int], R: list[int]) -> int:
    fixed_xor = 0
    max_free_bit = -1
    
    for i in range(N):
        l, r = L[i], R[i]
        if l == r:
            fixed_xor ^= l
        else:
            # Find the most significant bit where L[i] and R[i] differ
            diff_bit = (l ^ r).bit_length() - 1
            
            # Bits above diff_bit are identical in L[i] and R[i] (fixed)
            high_mask = ~((1 << (diff_bit + 1)) - 1)
            fixed_xor ^= (l & high_mask)
            
            # Record the highest bit position where we have full flexibility
            if diff_bit > max_free_bit:
                max_free_bit = diff_bit
                
    if max_free_bit != -1:
        free_mask = (1 << (max_free_bit + 1)) - 1
        return (fixed_xor & ~free_mask) | free_mask
    else:
        return fixed_xor

def main():
    T = int(input())
    for _ in range(T):
        N = int(input())
        L = list(map(int, input().split()))
        R = list(map(int, input().split()))
        print(solve(N, L, R))

if __name__ == '__main__':
    main()
