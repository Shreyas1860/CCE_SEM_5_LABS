import re

regex = r'^[a-z]$|^([a-z]).*\1$'

st = input("Enter string: ")
if(re.search(regex, st)):
    print("valid")
else:
    print("Invalid")