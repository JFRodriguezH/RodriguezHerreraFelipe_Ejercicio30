import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("poisson.dat")

Nx = len(data[0, :])-1

x = np.linspace(-1,1,Nx)
t = data[:, 0]
X, T = np.meshgrid(x, t)
Z = data[:, 1:]
print(Z[-1, int(Nx/2)]-Z[-2, int(Nx/2)])
plt.figure(figsize=(12,4))
plt.subplot(1,3,1)
plt.imshow(Z, aspect=0.1)
plt.subplot(1,3,2)
plt.plot(x, Z[-1, :])
plt.scatter(x[int(Nx/2-1)], Z[-1, int(Nx/2-1)], label=Z[-1, int(Nx/2-1)])
plt.legend()
plt.subplot(1,3,3)
plt.plot(t, Z[:, int(Nx/2)])
plt.tight_layout()

plt.savefig("poisson_"+str(Nx)+".png")