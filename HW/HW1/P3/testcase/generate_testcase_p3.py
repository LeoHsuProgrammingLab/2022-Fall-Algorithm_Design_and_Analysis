import random

path = "testcase_p3.txt"
n = 1000

temp1, temp2 = 0, 0

with open(path, "w") as f:
    f.write(f"{n}\n")
    f.write("-1000000000 1 0 1000000000\n")
    for i in range(n):
        # if(i%2 == 0):
        a = random.randint(0, 1000000000)
        b = random.randint(10, 10)
        temp1, temp2 = a, b
        # else:
        #     # a = random.randint(0, 1000000001)
        #     a = temp1
        #     # b = temp2
        #     b = random.randint(0, 1000000001)
    
        f.write(f"{a} {b}\n")