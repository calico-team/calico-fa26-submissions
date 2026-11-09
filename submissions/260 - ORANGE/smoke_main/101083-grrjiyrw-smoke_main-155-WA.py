Charge=2
M=-1
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
      for i in range (len(AI)):
         AII=list(map(int,AI))
         AII[-1]=0
         if (AII[M+1])-(AII[M])<RI and Charge==0:
            print("NO")
            Charge=2
            M=-1
            break
         elif (AII[M+1])-(AII[M])<RI and M+2<NI:
            M=M+1
            Charge=Charge-1

         elif (AII[M+1])-(AII[M])==RI and M+2<NI:
            M=M+1

         elif (AII[M+1])-(AII[M])>RI*Charge:
            M=M+1
            Charge=Charge+1

         else:
            print("YES")
            Charge=2
            M=-1
            break
      break