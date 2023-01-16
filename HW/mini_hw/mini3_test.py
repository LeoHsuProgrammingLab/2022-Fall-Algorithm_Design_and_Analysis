import random

n = input('please input n: ')
m = input('please input m: ')


with open('sample1.txt', 'w') as f:
    for i in range(int(m)):
        if i == 0:
            f.write(f"{n} {m}\n")
        a = random.randint(1, int(n))
        b = random.randint(1, int(n))
        f.write(f"{a} {b}\n")

