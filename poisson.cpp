#include <iostream>
#include <fstream>
#include<math.h>

/*dP/dt = D* d^2P/dx^2 + s */
float const D = 1.0;
float const S = 1.0;
float const tf = 1.0;
float const error = pow(10, -5);


void buildg(float** g, int Nx, float Dt, float Dx);
void avance(float** g, float* prev, float* next, int Nx, float Dt);
std::ofstream outfile;

int main(int argv, char** argc){
	std::string num = argc[1];
	int Nx = std::stoi(num);
    float Dx = 2.0/Nx;
    float Dt = (Dx*Dx)/(2.0*D);
	int Nt = tf/Dt;
	
	float** g_A = new float*[Nx];
	for(int i=0;i<Nx;i++){
		g_A[i] = new float[Nx];
	}
	buildg(g_A, Nx, Dt, Dx);
	
	float* temp_A = new float[Nx];
	float* sol_A = new float[Nx];
	
	float previo = temp_A[Nx/2];
	
	float t = 0;
	outfile.open("poisson.dat");	
	outfile<<t<<" ";
	for(int j=0;j<Nx;j++){
		outfile<<sol_A[j]<<" ";
	}
	outfile<<std::endl;
	t += Dt;
	avance(g_A, temp_A, sol_A, Nx, Dt);
	float nuevo = sol_A[Nx/2];
	
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
	outfile<<t<<" ";
	for(int j=0;j<Nx;j++){
		outfile<<sol_A[j]<<" ";
	}
	outfile<<std::endl;
	
	outfile.close();
	delete [] g_A;
	delete [] temp_A;
	delete [] sol_A;
	return 0;
}


void buildg(float** g, int Nx, float Dt, float Dx){
	float temp = D*Dt/(Dx*Dx);
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

void avance(float** g, float* prev, float* next, int Nx, float Dt){
	float temp;
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