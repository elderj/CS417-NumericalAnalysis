#ifndef LUDECOMPOSITION_H
#define LUDECOMPOSITION_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "AugmentedMatrix.h"
#include <vector>
#include <math.h>


using namespace std;

class LUDecomposition
{
    private:
        unsigned short int rows;
        unsigned short int cols;
        unsigned int mtxSize;
        bool solved = false;


        vector<vector<double> > mtxA;    vector<double> mtxB;
        vector<vector<double> > mtxU;    vector<vector<double> > mtxL;

        int iterations = 0;
        vector<double> xNew;
        //const double TOLERABLEERROR = .00001;

    public:
        LUDecomposition(vector<double> & nput);
        void SetMatrices(int rows, int cols, vector<double> & nput);
        void Decompose();
        void PrintLU();
        void Finisher();
        void Output();

};

#endif
