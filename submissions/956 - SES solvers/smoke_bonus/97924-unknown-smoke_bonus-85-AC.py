def smoke():
         inp=int(input())
         for i in range(inp):
           val=input().split()
           smoke=int(val[0])
           recharge=int(val[1])
           final=input().split()
           final=[int(x) for x in final]
           avail=2
           ready=0
           chance=True

           for z in final:
              while avail<2 and ready<=z:
                   avail=avail+1
                   ready=ready+recharge
              if avail==0:
                chance=False
                break
              avail=avail-1
              if avail==1:
                ready=z+recharge
           
           print("YES" if chance else "NO")
  
if __name__=="__main__":
      smoke()
