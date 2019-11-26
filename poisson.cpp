#include <iostream>
#include <fstream>
#include<math.h>

/*dP/dt = D* d^2P/dx^2 + s */
double const D = 1.0;
double const S = 1.0;
double const tf = 1.0;
double const error = pow(10, -6);


void buildg(double** g, int Nx, double Dt, double Dx);
void avance(double** g, double* prev, double* next, int Nx, double Dt);
std::ofstream outfile;

int main(int argv, char** argc){
	int Nx = atoi(argc[1])+1;
    double Dx = 2.0/Nx;
    double Dt = (Dx*Dx)/(2.0*D);
	int Nt = tf/Dt;
	
	double** g_A = new double*[Nx];
	for(int i=0;i<Nx;i++){
		g_A[i] = new double[Nx];
	}
	buildg(g_A, Nx, Dt, Dx);
	
	double* temp_A = new double[Nx];
	double* sol_A = new double[Nx];
	
	double previo = temp_A[Nx/2];
	
	std::string filename = "poisson_";
	filename.append(argc[1]);
	filename.append(".dat");

	outfile.open(filename);
	
	double t = 0;
	outfile<<t<<" ";
	for(int j=0;j<Nx;j++){
		outfile<<sol_A[j]<<" ";
	}
	outfile<<std::endl;
	t += Dt;
	avance(g_A, temp_A, sol_A, Nx, Dt);
	double nuevo = sol_A[Nx/2];
	
	while((nuevo-previo)>error){
        outfile<<t<<" ";
		for(int j=0;j<Nx;j++){
			outfile<<sol_A[j]<<" ";
		}
		outfile<<std::endl;
		t += Dt;
		previo = sol_A[Nx/2];
		avance(g_A, temp_A, sol_A, Nx, Dt);
		nuevo = sol_A[Nx/2];
	}
	
	outfile.close();
	delete [] g_A;
	delete [] temp_A;
	delete [] sol_A;
	return 0;
}


void buildg(double** g, int Nx, double Dt, double Dx){
	double temp = D*Dt/(Dx*Dx);
	for(int i=1;i<Nx-1;i++){
		for(int j=1;j<Nx-1;j++){
			if(i==j){
				g[i][j]=-2.0*temp+1;
				if(j!=0){
					g[i][j-1]=1.0*temp;
				}
				if(j!=(Nx-1)){
					g[i][j+1]=1.0*temp;
				}
			}
		}
	}
}

void avance(double** g, double* prev, double* next, int Nx, double Dt){
	double temp;
	for(int j=1;j<Nx-1;j++){
		temp = 0;
		for(int k=0;k<Nx;k++){
			temp += g[j][k]*prev[k];	
		}
		next[j] = temp+Dt*S;
	}
	for(int k=0;k<Nx;k++){
		prev[k] = next[k];	
	}
}