poisson.dat : poisson.dat poisson.py
	./poisson.out 10
	python poisson.py
	rm poisson.dat
	./poisson.out 30
	python poisson.py
	rm poisson.dat
	./poisson.out 100
	python poisson.py
	rm poisson.dat

poisson.out : poisson.cpp
	c++ poisson.cpp -o poisson.out