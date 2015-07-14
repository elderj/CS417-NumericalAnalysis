#ifndef BISECTION_H
#define BISECTION_H

#include <iostream>
#include <vector>
#include <math.h>
#include "Equation.h"



using namespace std;

class Bisection
{
    public:
        Bisection();
        void Solve();

    private:
        int iterations = 0;
        const double TOLERABLEERROR = .00001;
        bool solved = false;
        bool er = false;
        string inputEQ;
        double A;
        double B;
        double C;
        double finalC;

};
#endif
