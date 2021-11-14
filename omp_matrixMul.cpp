// Parallel takes omre time :)
// see other folder omp_mat.cpp

#include<omp.h>
#include<iostream>
using namespace std;

const int mx = 1000;
int i,j;

int main(int argc, char* argv[]){

	//freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int a[mx][mx], b[mx], c[mx];
	int thread_count ;
	thread_count = strtol(argv[1], NULL, 10);
	
	int r,cl;
	r = cl = mx;
	
	for(int i = 0; i < r; i++){
		for(int j = 0; j < cl; j++)
			a[i][j] = rand() % 100;
	}
	
	for(int i = 0; i < r; i++){
        	b[i] = rand()%100;
    	}
    	
    	// Serially Mulitiplication
    	clock_t start = clock();
    	for(int i = 0; i < r; i++){
    		c[i] = 0;
		for(int j = 0; j < cl; j++)
			c[i] += a[i][j]*b[j];
	}
	clock_t end = clock();
	double time = (double) (end - start)/ CLOCKS_PER_SEC;
	cout << "Serial Multiplication time : " << time * 1000.0 << " ms" << endl;
	/*for(int i = 0; i < r; i++){
        	cout << c[i] << " " ;
     	}*/
     	cout << endl;
     	
     	
     	//PARALLEL by openMP
     	
     	clock_t startp = clock();
     	#pragma omp parallel for num_threads(thread_count)\
     	default(none) shared(a,b,c,r,cl) private(i, j)
     	for(i = 0; i < r; i++){
    		c[i] = 0;
		for(j = 0; j < cl; j++)
			c[i] += a[i][j]*b[j];
	}
     	
     	clock_t endp = clock();
     	double timep = (double) (endp - startp)/ CLOCKS_PER_SEC;
	cout << "Parallel OMP Multiplication time : " << timep * 1000.0 << " ms" << endl;
	/*for(int i = 0; i < r; i++){
        	cout << c[i] << " " ;
     	}*/
     	cout << endl;
	
	
	
}
