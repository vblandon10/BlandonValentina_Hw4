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
