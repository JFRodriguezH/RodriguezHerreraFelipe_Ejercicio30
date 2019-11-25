poisson_30.png : poisson.dat poisson.py
	python poisson.py
	
poisson.dat : poisson.out
	./poisson.out 30

poisson.out : poisson.cpp
	c++ poisson.cpp -o poisson.out