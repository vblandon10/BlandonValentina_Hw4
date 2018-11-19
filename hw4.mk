all: p45.png proyectiles.png calcita_fFijas0.png calcita_fAbiertas0.png calcita_fPeriodicas0.png

p45.png proyectiles.png calcita_fFijas0.png calcita_fAbiertas0.png calcita_fPeriodicas0.png: proyectil.txt proyectil_info.txt fronterasFijas.txt fronterasAbiertas.txt fronterasPeriodicas.txt
	python plots.py


proyectil.txt proyectil_info.txt: ode.cpp
	g++ ode.cpp -o ode.x
	./ode.x

fronterasFijas.txt fronterasAbiertas.txt fronterasPeriodicas.txt: PDE.cpp makefile
	g++ PDE.cpp -o PDE.x
	fronterasFijas.txt
	./PDE.x 1 fronterasAbiertas.txt
	./PDE.x 2 fronterasPeriodicas.txt
