#ifndef NEWTON_H
#define NEWTON_H

#include <iostream>
#include <vector>
#include <math.h>
#include "Equation.h"

class Newton
{
    public:
        Newton();

    private:
        string inputEQ;
        void Solve(double xZ);
        int iterations = 0;
        const double TOLERABLEERROR = .00001;
        bool solved = false;
};

#endif // NEWTON_H
