def smoke():
         inp=input()
         inpu=int(inp)
         for i in range(inpu):
           smoke=input()
           recharge=input()
           final=input().split()
           final=[int(x) for x in final]
           avail=2
           ready=0
           chance=True

           for z in a:
              while avail<2 and ready<=z:
                   avail=avail+1
                   ready=ready+recharge
              if avail==0:
                chance=False
                break
              avail=avail-1
              if avail==1:
                  ready=z+recharge
              elif avail==0: 
                    ready=z+recharge
           print("YES" if chance else "NO")
 
                  
inp=input()     
if __name__=="__main__":
      smoke()
