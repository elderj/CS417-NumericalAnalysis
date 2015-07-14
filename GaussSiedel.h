#ifndef GAUSSSIEDEL_H
#define GAUSSSIEDEL_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;

class GaussSiedel
{
    private:


        int rows;
        int cols;
        int mtxSize = 0;
        vector<vector<double> > mtxA;    vector<double> mtxB;
        vector<vector<double> > mtxL;    vector<vector<double> > mtxU;
        vector<vector<double> > mtxLI;

        int iterations = 0;
        vector<double> xOld;
        vector<double> xNew;
        const double TOLERABLEERROR = .00001;
        //vector<double> errors;


        vector<double> mtxD;
        vector<vector<double> > mtxT;
        vector<vector<double> > aug;
        vector<double> mtxC;


        bool solved = false;

    public:
        GaussSiedel(vector<double> & nput);
        void SetMatrices(int rows, int cols, vector<double> & nput);
        void SetX();
        void SetL();
        void SetU();
        void GetLI();
        void printAug();
        void SetT();
        void SetC();
        void Solve();
        void Output();

};

#endif //GAUSSSIEDEL_h
