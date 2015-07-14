#ifndef TERM_H
#define TERM_H

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Term
{
public:

    //F's
    Term(string trm);
    double xVal(double x);
    void TermStats();
    string Derivative();


    //V's
    double coefficient;
    double exponent;
    string og;



private:
    bool sign;      ///0pos 1neg
    bool dig = true;       ///0no  1yes
    bool xUno = false;
    bool expn = false;
    bool hasCoef = true;
    string xterm;
    string coef;
    string expo;

    //bool trig;

};

#endif
