
cat =['I','I','D','J','Q']
s =input("enter a string in IDJO")
count = 0
while count >=4 or s!=cat :
    print("wrong")
    s =input()
    count =count+1
if s ==cat:
    print("correct")
