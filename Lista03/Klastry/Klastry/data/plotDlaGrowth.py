import sys
import numpy as np
import matplotlib.pyplot as plt

t, r = np.loadtxt("D:\\GitKraken\\Modelowanie-Komputerowe\\Lista03\\Klastry\\Klastry\\data\\dlaGrowth.txt", unpack=True)

plt.plot(t, r, "ro", label="r")
plt.plot(t, [rr*2 for rr in r], "mo", label="d")
plt.title("Promien klastra DLA w czasie")
plt.xlabel("time")
plt.ylabel("R")


plt.xscale("log")
plt.yscale("log")



plt.legend()    
plt.show()