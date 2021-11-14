#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

int main(int argc, char * argv[]){

    int thread_count = strtol(argv[1],NULL,10);
    double pi = 0.0, factor = 1.0;
    int n = 100000, i;
    
    #pragma omp parallel for num_threads(thread_count)\
    	reduction(+ : pi) private(factor, i)
    for(i = 0; i <= n; i++){
    	if(i % 2 == 0){
    		factor = 1.0;
    		pi += factor/ (2*i + 1);
    	}
    	else{
    		factor = -1.0;
    		pi += factor/ (2*i + 1);
    	}
    }
    
     cout<<"PI : "<< pi * 4.0<<endl;

    return 0;
}
