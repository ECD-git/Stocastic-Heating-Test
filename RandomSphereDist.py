import numpy
import matplotlib.pyplot as plt
import os

def ReadFile(name):
    return numpy.genfromtxt(name, delimiter=',')

dat = ReadFile("randsphere.dat")

fig = plt.figure()
ax = plt.axes(projection='3d')
ax.scatter(dat[:,0], dat[:,1], dat[:,2])
ax.set_title('Uniformly Weighted Random Unit Vector Plot, N={0:3.2f}'.format(numpy.size(dat, axis=0)))
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
plt.show()


