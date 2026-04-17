#include<iostream>
#include<cstdlib>
#include<vector>
#include <algorithm>

#include"Tensor.h"
#include"Conv.h"

using namespace std;

int Tensor::get_idx(int c, int y, int x) const{
        return (c * height * width) + (y * width) + x;}

void Tensor::rnd_set_initialize() {
        for(int i=0; i < channels; i++){
            for(int j=0; j< height; j++){
                for(int k=0; k < width; k++)
                    // assumo 8 bit
                    img[get_idx(i,j,k)] = rand() % 257;
                
            }
        }
    }

void Tensor::set_1(){
        for(int i=0; i < channels; i++){
            for(int j=0; j< height; j++){
                for(int k=0; k < width; k++)
                    // assumo 8 bit
                    img[get_idx(i,j,k)] = 1;
            }
        }
    }

void Tensor::set_blur_kernel() {
    // i pesi per un blur kernel standard
    float weights[9] = {
        1.0f/16.0f, 2.0f/16.0f, 1.0f/16.0f,
        2.0f/16.0f, 4.0f/16.0f, 2.0f/16.0f,
        1.0f/16.0f, 2.0f/16.0f, 1.0f/16.0f
    };

    for (int c = 0; c < channels; c++) {
        for (int i = 0; i < 9; i++) {
    
            int y = i / 3;  // mi dice in che riga sono (es. 3<i<5 riga 1)
            int x = i % 3;  // mi dice in che colonna sono (es. resto 2-> riga 2)
            img[get_idx(c, y, x)] = weights[i];
        }
    }
    }

void Tensor::print() const {
for (int c = 0; c < channels; c++) {
    cout << "Canale" << c << " " << endl;
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            float val = img[get_idx(c, h, w)];
            // Stampa con un decimale per vedere l'effetto blur
            //printf("%5.1f ", val); 
            cout << val;
            if(val > 100)
                cout << " ";
            else
                cout << "  ";
        }
        cout << endl;
    }
}
}

