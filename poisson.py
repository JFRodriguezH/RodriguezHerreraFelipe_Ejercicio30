import numpy as np
import matplotlib.pyplot as plt

n = np.array([10, 20, 30, 40, 50, 60, 70, 80, 90, 100])
N = np.array([])
cent = np.array([])
con = np.array([])

for i in n:
	data = np.loadtxt("poisson_"+str(i)+".dat")
	N = np.append(N, len(data[:, 0]))
	num = data[-1, int(i/2)]
	ana = 0.5
	cent = np.append(cent, np.abs((num-ana)/num))
	con = np.append(con, np.abs(data[-1, int(i/2)]-data[-2, int(i/2)]))
	

plt.figure(figsize=(12,4))
plt.subplot(131)
plt.ylabel('N iteraciones')
plt.xlabel('N_x')
plt.plot(n, N)
plt.subplot(132)
plt.ylabel('Error centro (%)')
plt.xlabel('N_x')
plt.plot(n, ((1e2)*cent))
plt.subplot(133)
plt.ylabel('Error convergencia x10^6')
plt.xlabel('N_x')
plt.ylim(0.999,1.001)
plt.plot(n, ((1e6)*con))
plt.tight_layout()
plt.savefig('resultado.png')