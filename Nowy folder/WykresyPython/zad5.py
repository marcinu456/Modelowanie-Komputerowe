import sys
import numpy as np
import plotly.express as px

x, y, z = np.loadtxt('spacery/3D/spacer(%s).txt'%(sys.argv[1]), unpack=True)
fig = px.scatter_3d(x=x, y=y, z=z)

fig.show()