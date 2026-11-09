
import sys
from collections import deque


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return


    idx = 0
    t = data[idx]
    idx+=1

    answers = []

    for _ in range(t):
        n = data [idx]
        r = data[idx + 1]
        idx +=2

        charges = 2
        recharge_done = deque()
        possible = True


        for j in range(n):
            a = data[idx]
            idx +=1

            while recharge_done and recharge_done[0] <= a:
                recharge_done.popleft()
                if charges < 2:
                    charges += 1

            if charges == 0:
                possible = False
                idx += ( n - j - 1)
                break

            charges -= 1


            if recharge_done:
                recharge_done.append(recharge_done[-1] + r)
            else:
                recharge_done.append(a + r)
        
        answers.append("YES" if possible else "NO")

    sys.stdout.write("\n".join(answers) + "\n")

if __name__ == "__main__":
    main()
