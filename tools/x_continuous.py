from matplotlib import pyplot as plt
import numpy as np


plt.xlabel("length of x")
plt.ylabel("number")

for i in range(5):
    print("data{}".format(i))
    with open("../data/dat{}_in".format(i)) as f:
        t = f.readline()
        arr = [0] * 10000000
        prev = ""
        cnt = 1
        for ch in t:
            if prev == 'x' and ch == 'x':
                cnt += 1
            elif prev == 'x':
                arr[cnt] += 1
                cnt = 1
            prev = ch
        while arr[-1] == 0:
            arr.pop()
        y = np.array(arr)
        plt.plot(y)
plt.show()
