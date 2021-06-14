import sys
import numpy as np
import matplotlib.pyplot as plt

s, i = np.loadtxt(sys.argv[1], unpack=True)
print(type(s))
plt.plot(s, i, "b1")#, label="a")
plt.plot([0,1],"r")#, label="a")

plt.axis('equal')


plt.legend()    
plt.show()