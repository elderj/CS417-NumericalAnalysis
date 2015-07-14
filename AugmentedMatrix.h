#ifndef AUGMENTEDAMTRIX_H
#define AUGMENTEDAMTRIX_H
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

class AugmentedMatrix
{
    private:

        unsigned int aRows;
        unsigned int aCols;

    public:
        AugmentedMatrix(vector<vector<double> > & mtxA ,vector<double> & mtxB);
        vector<vector<double> > value;

        void Print();
        vector<double> RREF();

};

#endif //AUGMENTEDAMTRIX_H
