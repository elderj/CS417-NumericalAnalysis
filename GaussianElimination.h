#ifndef GAUSSIANELIMINATION_H
#define GAUSSIANELIMINATION_H
#include <iostream>
#include <fstream>
#include <vector>
#include "AugmentedMatrix.h"

using namespace std;


class GaussianElimination
{

private:
    vector<vector<double> > mtxA;
    vector<double> mtxB;
    short unsigned int rows;
    short unsigned int cols;
    int mtxSize = 0;

public:
    GaussianElimination(vector<double> & nput);
    void SetMatrices(int rows, int cols, vector<double> & mtxData);
    void Solve();
    void Output();
};



#endif //GAUSSIANELIMINATION_H
