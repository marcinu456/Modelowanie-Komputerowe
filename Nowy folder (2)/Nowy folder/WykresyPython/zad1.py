import sys
import numpy as np
import matplotlib.pyplot as plt

i,c_rand,mt_rand = np.loadtxt("randData.txt", unpack=True)
plt.scatter(i,c_rand, label="rand()")
plt.scatter(i,mt_rand, label="std::mt19937")

plt.title("random generator comparasion")
plt.xlabel("Number")
plt.ylabel("Occurence count")
plt.legend()    
plt.show()