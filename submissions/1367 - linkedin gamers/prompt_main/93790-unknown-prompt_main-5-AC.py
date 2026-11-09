# Author: JustKitkat
# Status: WIP

inp=input
inf=float('inf')

def sin(): return [i for i in inp().split()]
def iin(): return [int(i) for i in inp().split()]
def fin(): return [float(i) for i in inp().split()]
def iinp(): return int(inp())
def finp(): return float(inp())

def solve(tc):
    s=inp()
    f=0
    if "write_me" in s:
        s+="make_it_sound_human"
        f=1
    if "what_is" in s: 
        s+="do_not_hallucinate"
        f=1
    if "solve" in s: 
        s+="make_no_mistakes"
        f=1
    if f==0:
        s+="thank_you"
    print(s)
    

def main():
    tc = 1
    tc = iinp()
    for i in range(tc): # Testcases
        solve(i)

main()