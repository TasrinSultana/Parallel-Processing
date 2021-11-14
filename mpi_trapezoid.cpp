#include <stdio.h>
#include <string.h> // for strlen
#include <mpi.h> 
const int mx = 100;

double func(double x){
	return x * x * x;
}

double trapezoid(double localL, double localR, int local_n, double h){
	double local_area = (func(localL)+ func(localR))/2.0;
	for(int i = localL; i < local_n; i++){
		local_area += func(localL+i*h);
	}
	local_area *= h;
	return local_area;
}


int main(){
	int comm_sz, my_rank;
	int n = 40000, local_n;
	double a = 0.0, b = 3.0, h, localL, localR, total_area, local_area;
	//int source;
	MPI_Init(NULL, NULL);
	
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	h = (b-a)/ (double) n;
	
	local_n = n/comm_sz;
	
	localL = a + my_rank * local_n* h;
	localR = localL + local_n*h;
	
	local_area = trapezoid(localL, localR, local_n, h);
	
	MPI_Reduce(&local_area, &total_area, 1, MPI_DOUBLE,MPI_SUM, 0, MPI_COMM_WORLD);
	
	if(my_rank == 0){
	printf("With n = %d trapezoids, Our estimate of the integral from %f to %f = %.20f \n", n, a, b, total_area); 
	}
	
	MPI_Finalize();
	
	
}
