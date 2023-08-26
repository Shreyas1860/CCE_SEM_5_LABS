import random

dic = {}

x = int(input("Enter number of elements: "))
datatype = "number"

for elem in range(x):
    y = input("Enter element to be added to dictionary ")
    if y.isnumeric() and datatype == "number":
       y = int(y);
    dic[random.randint(0,100)] = y;
    if isinstance(y, str):
        datatype = "string"

print ("\nDatatype : ", datatype)
res = ""
avg = 0
if datatype == "string":
    print("Concatenating all strings: ")
    for elem in dic:
        res += dic[elem]
    print(res)
else:
    print("Average of all elements: ")
    for elem in dic:
        avg += dic[elem]
    avg = avg/len(dic)
    print(avg)

if datatype == "string":
    x = input("\nEnter element to be searched: ");
    for key in dic:
        if dic[key] == x:
            print("Element present at ", key)

if datatype == "string":
    print("\nSpecial Characters: ")
    special_characters='[](){}<>\/!@#$%^&_*-+=|:`~'
    for key in dic:
        for char in dic[key]:
            if char in special_characters:
                print(dic[key], " has special characters")
                break
