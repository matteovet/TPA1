#ifndef CONV_H
#define CONV_H

#include<iostream>
#include<vector>
#include"Tensor.h"

using namespace std;

class Convolution{
private:
    int k_size;

    public:
    Convolution(int k): k_size(k) {}
    
    void compute(const Tensor& in, const Tensor& kernel, Tensor& out);


};
#endif