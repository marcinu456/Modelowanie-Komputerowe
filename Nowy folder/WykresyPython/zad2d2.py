import sys
import numpy as np
import plotly.express as px

x, y = np.loadtxt('spacery/2D/spacer(%s).txt'%(sys.argv[1]), unpack=True)
fig = px.scatter(x=x, y=y)

fig.show()