#include<iostream>
#include<cstdlib>
#include<vector>
#include<cmath>
#include<omp.h>

#include"Tensor.h"
#include"Conv.h"

using namespace std;

void Convolution::compute(const Tensor& in, const Tensor& kernel, Tensor& out) {
    if (in.channels != kernel.channels) {
        cerr << "Kernel ed input devono avere lo stesso numero di canali" << endl;
        return; 
    }

    int k_half = k_size / 2;

    //opzione 1: parallelizzo solo i canali
#pragma omp parallel for schedule(static)
//opzione 2: parallelizzo c ed h
//#pragma omp parallel for collapse(2)
for (int c = 0; c < in.channels; c++) {

    //opzione 3: parallelizzo su h e w
    //#pragma omp parallel for collapse(2)
    for (int w = 0; w < in.width; w++) {
    for (int h = 0; h < in.height; h++) {
        
            
            float sum = 0.0f;
            //loop sul kernel
            for (int kh = 0; kh < k_size; kh++) {
                for (int kw = 0; kw < k_size; kw++) {
                    //Mappo la posizione del pixel
                    int in_y = h + kh - k_half;
                    int in_x = w + kw - k_half;

                    float pixel = 0.0f;
                    // padding -> verifico che il pixel sia all'interno dell'immagine
                    if (in_y >= 0 && in_y < in.height && in_x >= 0 && in_x < in.width) {
                        pixel = in.img[in.get_idx(c, in_y, in_x)];
                    }

                    float k_val = kernel.img[kernel.get_idx(c, kh, kw)];

                    sum += pixel * k_val; 
                    
                }
            }

            // Clipping per immagine 8 bit
            if (sum > 255.0f) sum = 255.0f;
            if (sum < 0.0f) sum = 0.0f;

            out.img[out.get_idx(c, h, w)] = round(sum); // si usano valori interi per i pixel
        }
    }
    
}
}
