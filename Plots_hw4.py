from numpy import *
from matplotlib.pyplot import *

proyectiles = genfromtxt("proyectil.txt")
info_proyectiles = genfromtxt("proyectil_info.txt")

ip = np.cumsum(info_proyectiles) # indices de los proyectiles

print(ip)

i0 = int(0)
i1 = int(ip[0])


print(i0, i1)
figure()
plot(proyectiles[i0:i1,0], proyectiles[i0:i1,2])
savefig('p45.png')

figure()
for i in range(6):
	i0 = int(ip[i])
	i1 = int(ip[i+1])
	plot(proyectiles[i0:i1,0], proyectiles[i0:i1,2], label=str((i+1)*10))
i0=int(ip[-1])
i1=-1
plot(proyectiles[i0:i1,0], proyectiles[i0:i1,2], label=str(70))
legend(loc='best')
savefig('proyectiles.png')
