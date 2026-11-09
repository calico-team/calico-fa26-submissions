import sys
import heapq


def solve():
    input = sys.stdin.readline

    T = int(input())

    for _ in range(T):
        N, R = map(int, input().split())
        A = list(map(int, input().split()))

        # Process requests in chronological order
        A.sort()

        # Initially, Omen has 2 available smoke charges
        available = 2

        # Min-heap stores recharge completion times
        recharge = []

        # Time when the previous recharge finishes
        last_finish = 0

        possible = True

        for t in A:

            # Complete all recharges that finish by time t
            while recharge and recharge[0] <= t:
                heapq.heappop(recharge)
                available += 1

            # No smoke charge available
            if available == 0:
                possible = False
                break

            # Use one smoke charge
            available -= 1

            # Recharge starts after the previous recharge
            start = max(t, last_finish)
            finish = start + R

            last_finish = finish
            heapq.heappush(recharge, finish)

        print("YES" if possible else "NO")


if __name__ == "__main__":
    solve()