import random

path = "testcase.txt"

n = input("please input n:")
m = input("please input m:")

with open(path, "w") as f:
    f.write(f"{n} {m}\n")
    for i in range((int)(m)):
        if i < ((int)(n)) - 1 :
            f.write(f"{i+1} {i+2} 1\n")
        else:
            f.write(f"{i+1} 1 1\n")