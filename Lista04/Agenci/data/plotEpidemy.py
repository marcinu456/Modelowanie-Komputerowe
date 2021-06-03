import sys
import numpy as np
import matplotlib.pyplot as plt

# usage - <program name> <file name>

"""
"""


s, i, r = np.loadtxt(sys.argv[1], unpack=True)

plt.plot(range(len(s)), s, "b-", label="podatny")
plt.plot(range(len(s)), i, "r-", label="zainfekowany")
plt.plot(range(len(s)), r, "g-", label="ozdrowiony")
#plt.plot(t, t**(1.75), "b-", label="N**(1.74)")
plt.title("population " + sys.argv[1])
plt.xlabel("czas")
plt.ylabel("liczba")



#plt.xscale("log")
#plt.yscale("log")



plt.legend()    
plt.show()