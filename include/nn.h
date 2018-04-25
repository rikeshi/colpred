#pragma once
#include "matrix.h"
#include <math.h>

typedef struct NeuralNetwork {
    float lr;
    int ni;
    int nh;
    int no;
    Matrix *i;
    Matrix *h;
    Matrix *o;
    Matrix *w_ih;
    Matrix *w_ho;
    Matrix *b_h;
    Matrix *b_o;
} NeuralNetwork;

NeuralNetwork *create_nn(size_t ni, size_t nh, size_t no);
int destroy_nn(NeuralNetwork *nn);
Matrix *sigmoid(Matrix *m);
Matrix *gradients(Matrix *m);
Matrix *nn_predict(NeuralNetwork *nn, float *ax);
// TODO
void nn_train(NeuralNetwork *nn, float *ay);


