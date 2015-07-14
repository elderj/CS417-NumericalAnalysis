#ifndef JACOBI_H
#define JACOBI_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <vector>
#include <math.h>


using namespace std;

class Jacobi
{
    private:

        ///Solving stuff
        unsigned short int rows;
        unsigned short int cols;
        unsigned int mtxSize;
        int iterations = 0;
        vector<double> xOld;
        vector<double> xNew;
        const double TOLERABLEERROR = .00001;
        bool solved = false;

        ///Matrices stuff
        vector<vector<double> > mtxA;    vector<double> mtxB;
        vector<vector<double> > mtxDI;
        vector<vector<double> > mtxU;   vector<vector<double> > mtxL;
        vector<vector<double> > mtxT;
        vector<double>  mtxC;



    public:
        Jacobi(vector<double> & nput);
        void SetMatrices(int rows, int cols, vector<double> & nput);
        void SetDI();
        void SetU();
        void SetL();
        void SetT();
        void SetC();
        void SetX();
        void Solve();
        void Output();
};

#endif
