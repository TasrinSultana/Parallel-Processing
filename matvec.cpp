#include<bits/stdc++.h>
#include<pthread.h>

using namespace std;

const int MX = 1000;
int thread_count, y[MX], n, A[MX][MX], X[MX];

// function to run from creating a thread
void * hello(void * rank){
    long my_rank = (long) rank;
    cout<<"printing from :"<<my_rank<<endl;
    int localFR, localLR;
    int local_n = n/thread_count;
    localFR = my_rank * local_n;
    localLR = ((my_rank+1) * local_n)-1;
    
    for(int i = localFR; i <= localLR; i++){
    	y[i] = 0;
    	for(int j = 0; j < n; j++){
    		y[i] += A[i][j]*X[j];
    		cout << my_rank << " " << y[i] << " is it updating?" << endl;
    	}
    }
    return NULL;
}

int main(int argc, char * argv[]){
    long thread;
    pthread_t * thread_handels;

    thread_count = strtol(argv[1], NULL, 10); // reading number of thread from the commmnad line
    // allocating thread handles object which is opaque object
    thread_handels = (pthread_t *) malloc(thread_count * sizeof(pthread_t));
    //A[3][2] = {{1, 2, 3}, {1, 2, 3} };
    
    //X[2] = {1, 1};
    int row, colom;
    cout << "Row, colom: " << endl;
    cin >> row >> colom;
    for(int i = 0; i < row; i++){
    	for(int j = 0; j < colom; j++){
    		cin >> A[i][j];
    	}
    }
    
    for(int i = 0; i < colom; i++){
    	cin >> X[i];
    }
    n = row;
    


    // starting thread with the thread create function
    for(thread = 0; thread < thread_count; thread++){
        pthread_create(&thread_handels[thread], NULL, hello, (void *) thread);
    }

    // joining or ending threads by this segment
    for(thread = 0; thread < thread_count; thread++){
        pthread_join(thread_handels[thread], NULL);
    }
    
    puts("printing from main program");
    cout << endl;
    for(int i = 0; i < colom; i++){
    cout << y[i] << endl;
    }

    // freeing allocated memory by malloc fucntion 
    free(thread_handels);

    return 0;
}
