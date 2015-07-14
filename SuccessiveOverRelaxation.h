#ifndef SUCESSIVEOVERRELAXATION_H
#define SUCESSIVEOVERRELAXATION_H
#include <vector>
#include <iostream>
#include <math.h>


#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;

class SuccessiveOverRelaxation
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
        vector<double> xOmega;
        double omega = 1.2;

        ///Solving Vars
        const double TOLERABLEERROR = .00001;
        bool solved = false;
        vector<double> mtxD;
        vector<vector<double> > mtxT;
        vector<vector<double> > aug;
        vector<double> mtxC;


    public:
        SuccessiveOverRelaxation(vector<double> & nput);
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


#endif //SUCESSIVEOVERRELAXATION
