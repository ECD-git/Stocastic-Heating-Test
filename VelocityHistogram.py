import numpy
import matplotlib.pyplot as plt
import os

Ma = 1.00784*1.66*(10**(-27))
k_B = 1.380649*(10**(-23))

def MaxBoltPDF(v, T, U):
    E = 0.5*Ma*(v**2) + U;
    return numpy.sqrt(2/numpy.pi) *2* numpy.sqrt((Ma)/(k_B*T)) * (E/(k_B*T)) * numpy.exp(-E/(k_B*T))

def ReadFile(name):
    return numpy.genfromtxt(name, delimiter=',')

dat = ReadFile("mbhisttest.dat")
print(dat)

Temp = dat[1]
PE = dat[0]
dat = dat[2:]

fig = plt.figure()
ax = plt.axes()
ax.set_title("Random Maxwell-Boltzman Distributed Velocities \n For $H$, N={0:3.0f}, U={1:1.1f}$k$, T={2:1.3f}$k$".format(numpy.size(dat), PE, Temp))

plt.hist(dat, bins=50, density=True, color='lightblue')

x = numpy.linspace(numpy.max(dat), numpy.min(dat), 50)
y = MaxBoltPDF(x, Temp, PE)

plt.plot(x,y,'k--', label="Maxwell-Boltzman Distribution")
plt.legend()

plt.xlabel("Velocity $ms^{-1}$")
plt.ylabel("bin density/probability density")

plt.show()