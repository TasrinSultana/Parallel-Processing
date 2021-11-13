#include<bits/stdc++.h>
#include<pthread.h>

using namespace std;

int n, my_n, flag, thread_count;
double sum;


void* thread_sum(void* rank){
	long my_rank = (long) rank;
	double factor;
	
	int fi, li;
	fi = my_rank * my_n;
	li = fi + my_n;
	double local_sum = 0.0;
	
	if(my_rank % 2 == 0){
		factor = 1.0;
	}
	else{
		factor = -1.0;
	}
	
	for(int i = fi; i < li; i++, factor = - factor){
		local_sum += factor/(2*i + 1);	
	}
	
	while(my_rank != flag);
	sum += local_sum;
	flag = (flag + 1)% thread_count;
	
	
	return NULL;
}

int main(int argc, char* argv[]){
	int thread;
	pthread_t* thread_handles;
	
	thread_count = strtol(argv[1], NULL, 10);
	n = strtol(argv[2], NULL, 10);
	my_n = n/ thread_count;
	sum = 0.0;
	flag = 0;
	
	thread_handles = (pthread_t *)malloc(thread_count * sizeof(pthread_t));
	clock_t begin = clock();
	
	for(thread = 0; thread < thread_count; thread++){
		pthread_create(&thread_handles[thread], NULL, thread_sum, (void *) thread);
	}
	
	for(thread = 0; thread < thread_count; thread++){
		pthread_join(thread_handles[thread], NULL);
	}
	
	free(thread_handles);
	
	clock_t end = clock();
	
	double time = end - begin;
	
	cout << "Value of PI = " << 4 * sum << endl;
	cout << "Time :" << time << endl;
	
}
