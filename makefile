resultado.png : poisson.out poisson.py
	./poisson.out 10
	./poisson.out 20
	./poisson.out 30
	./poisson.out 40
	./poisson.out 50
	./poisson.out 60
	./poisson.out 70
	./poisson.out 80
	./poisson.out 90
	./poisson.out 100
	python poisson.py
	rm poisson_10.dat poisson_20.dat poisson_30.dat poisson_40.dat poisson_50.dat poisson_60.dat poisson_70.dat poisson_80.dat poisson_90.dat poisson_100.dat
	
poisson.out : poisson.cpp
	c++ poisson.cpp -o poisson.out

clean : 
	rm poisson_10.dat poisson_20.dat poisson_30.dat poisson_40.dat poisson_50.dat poisson_60.dat poisson_70.dat poisson_80.dat poisson_90.dat poisson_100.dat
