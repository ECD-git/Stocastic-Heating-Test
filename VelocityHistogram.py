import numpy
import matplotlib.pyplot as plt
import os
import scipy

Ma = 1.00784*1.66*(10**(-27))
k_B = 1.380649*(10**(-23))

def MaxBoltPDF(v, T, U):
    E = 0.5*Ma*(v**2) + U;
    return numpy.sqrt(2/numpy.pi) *2* numpy.sqrt((Ma)/(k_B*T)) * (E/(k_B*T)) * numpy.exp(-E/(k_B*T))
def MaxBoltCDF(v, T, U):
    E = 0.5*Ma*(v**2) + U
    return scipy.special.erf(numpy.sqrt(E/(k_B*T)))- (2/numpy.sqrt(numpy.pi))*numpy.sqrt(E/(k_B*T))*numpy.exp(-E/(k_B*T))

def ReadFile(name):
    return numpy.genfromtxt(name, delimiter=',')

dat = ReadFile("mbhisttest.dat")
#print(dat)
Temp = dat[0,1] # pull out temp and U from the file
PE = dat[0,0]
dat = dat[1:] # data is in U(0,1), (corresponding velocity from CDF)

x = numpy.linspace(numpy.max(dat[:,1]), numpy.min(dat), 50)

fig, axes = plt.subplots(2)
fig.suptitle("Random Maxwell-Boltzman Distributed Velocities \n For $H$, N={0:3.0f}, U={1:1.1f}$k$, T={2:1.3f}$k$, Newt-Rhap Iterations = 50".format(numpy.size(dat)/2, PE, Temp))

# CDF plot
# take a random sample of prob values and their velocities
sample = dat[numpy.random.randint(dat.shape[0], size=8), :]
sample = numpy.append(sample, dat[numpy.where(dat[:,0] == numpy.max(dat[:,0]))[0]], axis=0)
sample = numpy.append(sample, dat[numpy.where(dat[:,0] == numpy.min(dat[:,0]))[0]], axis=0)
print(dat[numpy.where(dat[:,0] == numpy.max(dat[:,0]))[0][0]])

# plot the probs on the y axis
axes[0].scatter( numpy.zeros(numpy.size(sample[:,0])),sample[:,0])

# plot vel and prob
axes[0].scatter(sample[:,1], sample[:,0], marker='x')

# plot a line at y=prob value to show intersection with cdf
for i in sample:
    axes[0].plot(x, numpy.full(numpy.size(x),i[0]), 'r--')

CDFy = MaxBoltCDF(x, Temp, PE)
axes[0].plot(x, CDFy, 'k')
axes[0].set_title("Maxwell Boltzman CDF")

# PDF plot
axes[1].hist(dat[:,1], bins=50, density=True, color='lightblue')
PDFy = MaxBoltPDF(x, Temp, PE)
axes[1].plot(x,PDFy,'k--', label="Maxwell-Boltzman Distribution")
axes[1].legend()
axes[1].set_xlabel("Velocity $ms^{-1}$")
axes[1].set_ylabel("bin density/PDF")

print(numpy.max(dat[:,0]))
print(numpy.min(dat[:,0]))

# Lets make a focused plot of the inverse CDF process at the min and max probabilities
fig2, axes2 = plt.subplots(1,2)
fig2.suptitle("Random Maxwell-Boltzman CDF Distributed Velocities \n For $H$, N={0:3.0f}, U={1:1.1f}$k$, T={2:1.3f}$k$, Newt-Rhap Iterations = 50".format(numpy.size(dat)/2, PE, Temp))

mins = dat[dat[:, 0].argsort()][0:5]
maxs = dat[dat[:, 0].argsort()[::-1]][0:5]

# min values
x = numpy.linspace(3, numpy.min(mins), 50)
# plot the probs on the y axis
axes2[0].scatter( numpy.zeros(numpy.size(mins[:,0])),mins[:,0])
# plot vel and prob
axes2[0].scatter(mins[:,1], mins[:,0], marker='x')
# plot a line at y=prob value to show intersection with cdf
for i in mins:
    axes2[0].plot(x, numpy.full(numpy.size(x),i[0]), 'r--')
CDFy = MaxBoltCDF(x, Temp, PE)
axes2[0].plot(x, CDFy, 'k')
axes2[0].set_title("5 Most Minimum Values")
axes2[0].set_ylim(top=numpy.max(mins[:,0])*1.1, bottom =0)

# max values
xmax = numpy.linspace(numpy.max(maxs[:,1])*2, numpy.min(maxs), 25)
# plot the probs on the y axis
axes2[1].scatter( numpy.zeros(numpy.size(maxs[:,0])),maxs[:,0])
# plot vel and prob
axes2[1].scatter(maxs[:,1], maxs[:,0], marker='x')
# plot a line at y=prob value to show intersection with cdf
for i in maxs:
    axes2[1].plot(xmax, numpy.full(numpy.size(xmax),i[0]), 'r--')

CDFy = MaxBoltCDF(xmax, Temp, PE)
axes2[1].plot(xmax, CDFy, 'k')
axes2[1].set_title("5 Most Maximum Values")
axes2[1].set_ylim(top=1.0005, bottom=numpy.min(maxs[:,0])*0.9995)

fig2.set_figheight(6)
fig2.set_figwidth(12)
fig.set_figheight(8)
fig.set_figwidth(12)
plt.show()