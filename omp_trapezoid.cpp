#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

double func(double x){
    return x*x;
}


int main(int argc, char * argv[]){

    int thread_count = strtol(argv[1],NULL,10);
    double a, b, total_area = 0.0, h;
    int i, n;
    a = 2.0;
    b = 4.0;
    n = 4000;
    
    h = (b - a)/n;
    
    total_area += (func(a) + func(b))/2;
    
    # pragma omp parallel for num_threads(thread_count) \
        reduction(+ : total_area)  private(i)
    for(i = 1; i <= n-1 ; i++)
        total_area += func( a + h*i);
    total_area *= h;

    cout<<"total area = "<<total_area<<endl;
    

    return 0;
    
    
}
