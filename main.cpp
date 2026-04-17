#include<iostream>
#include <chrono>
#include<cstdlib>
#include<vector>

#ifdef _OPENMP
#include <omp.h>
#endif

#include"Tensor.h"
#include"Conv.h"


using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]){

    int size = (argc > 1) ? atoi(argv[1]) : 128;
    int channels = (argc > 2) ? atoi(argv[2]) : 3;
    int runs = (argc > 3) ? atoi(argv[3]) : 5;
    #ifdef _OPENMP
    int threads = (argc > 4) ? atoi(argv[4]) : 16;
    #endif

    #ifdef _OPENMP
        omp_set_num_threads(threads);
    #endif

    int k_size = 3;

    Tensor immagine(channels,size,size);
    Tensor out(channels,size,size);
    Tensor kernel (channels,k_size,k_size);

    srand(12);
    immagine.rnd_set_initialize();
    kernel.set_blur_kernel();
    Convolution conv(kernel.height);

    for(int i = 0; i < runs; ++i) {
        auto start = chrono::high_resolution_clock::now();
        conv.compute(immagine, kernel, out);
        auto end = chrono::high_resolution_clock::now();
        
        chrono::duration<double> diff = end - start;
        
        #ifdef _OPENMP
        cout << size << "," << channels << "," << threads << "," << diff.count() << endl;
        #else
        cout << size << "," << channels << "," << "1" << "," << diff.count() << endl;
        #endif
    } 
    return 0;
}