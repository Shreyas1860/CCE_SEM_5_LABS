def fun():
    a,b,c,d,e = 1,2,3,4,5
    str = "HELLO WORLD"

print("Total local variables: ", fun.__code__.co_nlocals)