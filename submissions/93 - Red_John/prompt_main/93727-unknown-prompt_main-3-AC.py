# ██████╗ ███████╗ █████╗ ██████╗     ██╗  ██╗██╗██╗     ██╗     ███████╗██████╗
# ██╔══██╗██╔════╝██╔══██╗██╔══██╗    ██║ ██╔╝██║██║     ██║     ██╔════╝██╔══██╗
# ██║  ██║█████╗  ███████║██║  ██║    █████╔╝ ██║██║     ██║     █████╗  ██████╔╝
# ██║  ██║██╔══╝  ██╔══██║██║  ██║    ██╔═██╗ ██║██║     ██║     ██╔══╝  ██╔══██╗
# ██████╔╝███████╗██║  ██║██████╔╝    ██║  ██╗██║███████╗███████╗███████╗██║  ██║
# ╚═════╝ ╚══════╝╚═╝  ╚═╝╚═════╝     ╚═╝  ╚═╝╚═╝╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝
#          ☠  D E A D   K I L L E R'S   T E M P L A T E  ☠

# ============================== IMPORTS ================================= #
import sys
from collections import defaultdict,Counter,deque

# ============================== CONSTANTS ================================= #
posINF = float('inf')
negINF = float('-inf')

# ============================== ULTRA FAST IO ================================= #

input = sys.stdin.readline
write = sys.stdout.write

def inp(): return input().strip()
def intInp(): return int(inp())
def mapInt(): return map(int, inp().split())
def mapStr(): return map(str, inp().split())
def listInt(): return list(map(int, inp().split()))
def listStr(): return list(map(str, inp().split()))
def listFloat(): return list(map(float, inp().split()))
def digsOfNum(X): return list(map(int,list(str(X))))

# Fast Output Helpers
def printLine(x): write(str(x) + "\n")
def printArr(arr): write(" ".join(map(str, arr)) + "\n")
def printYes(): write("YES\n")
def printNo(): write("NO\n")


# ============================== SOLVE FUNCTION ================================= #

def solve():
    s = inp()
    if "write_me" in s: s+= "make_it_sound_human"
    elif "what_is" in s: s+= "do_not_hallucinate"
    elif "solve" in s: s += "make_no_mistakes"
    else: s+= "thank_you"
    print(s)

# ============================== MAIN DRIVER ==================================== #

def main():
    for _ in range(intInp()): solve()

# ============================== EXECUTION ====================================== #

if __name__ == "__main__":
    main()