import sys
import numpy as np
import plotly.express as px

time, x,= np.loadtxt('spacery/1D/spacer(%s).txt'%(sys.argv[1]), unpack=True)
fig = px.scatter(x=time, y=x)

fig.show()