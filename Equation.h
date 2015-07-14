#ifndef EQUATION_H
#define EQUATION_H

#include "Term.h"
#include <vector>
#include <iostream>

using namespace std;


class Equation
{
    public:
        Equation( vector<string> & nput );
        void plugin( double x);
        void Derivative();
        double anzwer = 0;
        vector<Term> PrimeTerms;
        vector<Term> Terms;

    private:



};

#endif // EQUATION_H
