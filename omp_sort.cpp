#include<bits/stdc++.h>
#include<omp.h>

using namespace std;


int main(int argc, char * argv[]){

    int thread_count = strtol(argv[1],NULL,10);

    int i, tmp, n=20, ar[10000], phase;
    
    for(i = 0; i < n; i++){
        ar[i] =  rand()%100;
    }
    
    /*for(int phase = 0; phase < n; phase++){
    	if(phase % 2 == 0){
    		for(int i = 1; i < n; i++){
    			if(ar[i-1] > ar[i]){
    				tmp = ar[i];
    				ar[i] = ar[i-1];
    				ar[i-1] = tmp;
    			}
    		}
    	}
    	else{
    		for(int i = 1; i <  n-1; i++){
    			if(ar[i-1] > ar[i]){
    				tmp = ar[i];
    				ar[i] = ar[i-1];
    				ar[i-1] = tmp;
    			}
    		}
    	
    	}
    
    } */
    
     #pragma omp parallel num_threads(thread_count)\
     default(none) shared(ar, n) private(phase, i, tmp)
     for(int phase = 0; phase < n; phase++){
    	if(phase % 2 == 0){
    		#pragma omp for
    		for(int i = 1; i < n; i++){
    			if(ar[i-1] > ar[i]){
    				tmp = ar[i];
    				ar[i] = ar[i-1];
    				ar[i-1] = tmp;
    			}
    		}
    	}
    	else{
    		#pragma omp for
    		for(int i = 1; i <  n-1; i++){
    			if(ar[i-1] > ar[i]){
    				tmp = ar[i];
    				ar[i] = ar[i-1];
    				ar[i-1] = tmp;
    			}
    		}
    	
    	}
    
    } 
    
    
     puts("Sorted array :");
    for(i=0; i < n; i++){
        cout<<ar[i]<<" ";
    }
    puts("");   


}
