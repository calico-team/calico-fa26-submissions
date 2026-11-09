Charge=2
M=0
T=int(input(""))
for i in range (T):
   NR=str(input(""))
   X=NR.split()
   N=(X[0])
   R=(X[1])
   NI=int(N)
   RI=int(R)
   for i in range (NI):
      A=str(input(""))
      AI=A.split()
      while M+1<NI:
         AII=list(map(int,AI))
         if (AII[M+1])-(AII[M])>RI*Charge:
            print("NO")
            break
         elif M<NI:
            M=M+1
            print("NEXT")
         else:
            print("YES")
            break