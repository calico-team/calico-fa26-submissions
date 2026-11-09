import sys; import os

#igncrease recursion dept in case N is BERY BIG
sys . setrecursionlimit (   2000  )

def solve_case_la(L,R):
    mEmO_dict = {}
    
    def MAX__XOR__PART(Bit_Position, PREFIX_XOR, tightL, tight_R):
        if Bit_Position<0:
          return PREFIX_XOR
        
        STATE_KEY = (Bit_Position, tightL, tight_R)
        if STATE_KEY in mEmO_dict: return mEmO_dict[STATE_KEY]
        
        STaTeS = {  ( 0,  tightL,  tight_R )  }
        
        for i in range(len(L)):
          bit_L = (L[i] >> Bit_Position) & 1
          BitR = ( R [ i ] >> Bit_Position ) & 1
          NEXT____STATES = set()
          
          for parity, t_L, t_R in STaTeS:
            if not ( ( t_L & ( 1 << i ) ) and bit_L == 1 ):
                    NewTL = t_L if bit_L == 0 else (t_L & ~(1 << i))
                    new_t_R = t_R if BitR == 1 else (t_R & ~(1 << i))
                    NEXT____STATES.add( ( parity , NewTL , new_t_R ) )
            
            if not ((t_R & (1 << i)) and BitR == 0):
	            new_t_L = t_L if bit_L == 1 else (t_L & ~(1 << i))
	            new_t_R = t_R if BitR == 0 else (t_R & ~(1 << i))
	            NEXT____STATES.add((parity ^ 1, new_t_L, new_t_R))
          STaTeS = NEXT____STATES
            
        OddMasksList = []
        even_masks = []
        for p, l, r in STaTeS:
            if p == 1:
               OddMasksList.append((l, r))
            else:
              even_masks.append((l, r))
        
        res = 0
        if OddMasksList:
          best = 0
          for l, r in OddMasksList:
             best = max(best, MAX__XOR__PART(Bit_Position - 1, PREFIX_XOR | (1 << Bit_Position), l, r))
          res = best
        else:
            best = 0
            for l, r in even_masks:
                best = max(   best,    MAX__XOR__PART(   Bit_Position - 1, PREFIX_XOR, l, r   )   )
            res = best
            
        mEmO_dict[STATE_KEY] = res; return res

    InitialTightMask = (1 << len(L)) - 1
    return MAX__XOR__PART(61, 0, InitialTightMask, InitialTightMask)

def main():
    InputDataString = sys.stdin.read().split()
    if not InputDataString:
      return
    
    T = int(InputDataString[0])
    idx = 1
    OutputListData = []
    
    for _ in range(T):
        N = int(InputDataString[idx])
        idx += 1
        L = [int(x) for x in InputDataString[idx : idx + N]]
        idx += N
        R = [int(x) for x in InputDataString[idx : idx + N]]
        idx += N
        OutputListData.append(str(solve_case_la(L, R)))
        
    print(
        '\n'.join(OutputListData)
    )

if __name__ == "__main__":
  main()
