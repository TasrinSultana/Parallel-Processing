#include<bits/stdc++.h>
#include<pthread.h>

using namespace std;

int n, my_n, flag, thread_count;
double sum;
pthread_mutex_t mutex_variable;


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
	
	//while(my_rank != flag);
	pthread_mutex_lock(&mutex_variable);
	sum += local_sum;
	pthread_mutex_unlock(&mutex_variable);
	//flag = (flag + 1)% thread_count;
	
	
	return NULL;
}

int main(int argc, char* argv[]){
	long thread;
	pthread_t* thread_handles;
	
	thread_count = strtol(argv[1], NULL, 10);
	n = strtol(argv[2], NULL, 10);
	my_n = n/ thread_count;
	sum = 0.0;
	flag = 0;
	
	thread_handles = (pthread_t *)malloc(thread_count * sizeof(pthread_t));
	pthread_mutex_init(&mutex_variable, NULL);
	clock_t begin = clock();
	
	for(thread = 0; thread < thread_count; thread++){
		pthread_create(&thread_handles[thread], NULL, thread_sum, (void *) thread);
	}
	
	for(thread = 0; thread < thread_count; thread++){
		pthread_join(thread_handles[thread], NULL);
	}
	
	pthread_mutex_destroy(&mutex_variable);
	free(thread_handles);
	
	clock_t end = clock();
	
	double time = end - begin;
	
	cout << "Value of PI = " << 4 * sum << endl;
	cout << "Time :" << time << endl;
	
}
