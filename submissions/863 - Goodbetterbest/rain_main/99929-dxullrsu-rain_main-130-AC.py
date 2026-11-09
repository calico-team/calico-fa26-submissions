import sys

def solve():
    data = iter(sys.stdin.buffer.read().split())

    T = int(next(data))

    for _ in range(T):
        N = int(next(data))
        K = int(next(data))

        # Group drones by X + Y
        groups = {}

        for i in range(N):
            x = int(next(data))
            y = int(next(data))
            z = int(next(data))
            d = next(data)

            s = x + y

            if s not in groups:
                groups[s] = [[], []]

            if d == b'E':
                groups[s][0].append(x)
            else:
                groups[s][1].append(x)

        meetings = 0

        # Process each group
        for east, north in groups.values():

            east.sort()
            north.sort()

            left = 0
            right = 0

            # Count valid East-North meetings
            for x in east:

                while left < len(north) and north[left] < x:
                    left += 1

                right = max(right, left)

                while right < len(north) and north[right] <= x + K - 1:
                    right += 1

                meetings += right - left

        # Every drone collects K units initially
        answer = N * K - meetings

        print(answer)


if __name__ == "__main__":
    solve()