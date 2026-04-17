#ifndef TENSOR_H
#define TENSOR_H

#include<iostream>
#include<vector>
using namespace std;


class Tensor{
    public:
    int channels;
    int height;
    int width;
    vector<float> img;

    Tensor(int c, int h, int w): channels(c), height(h), width(w), img(c*h*w, 0.0f){}

    int get_idx(int c, int y, int x) const;
    void rnd_set_initialize();
    void set_1();
    void set_blur_kernel();
    void print() const;
};

#endif