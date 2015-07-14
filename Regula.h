
#ifndef REGULA_H
#define REGULA_H

#include <iostream>
#include <vector>
#include <math.h>
#include "Equation.h"

class Regula
{
    public:
        Regula();

    private:
        void Solve();
        const double TOLERABLEERROR = .00001;
        int iterations = 0;
        string inputEQ;
        double A;
        double B;
        double C;

        bool solved = false;

};

#endif // REGULA_H
