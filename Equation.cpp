#include "Equation.h"

Equation::Equation(vector<string> & nput)
{
    for(int i = 0; i < nput.size(); i++)
    {
        //cout << "Adding term " << nput[i] << " to equation." << endl;
        Terms.push_back(Term(nput[i]));
    }
}


void Equation::plugin(double x)
{
    double answer = 0;
    ///cout << "in->" << x << endl;
    for ( int i = 0; i< Terms.size(); i++)
    {
       //cout << "term val "  << Terms[i].xVal(x) << endl;
       answer = answer +  Terms[i].xVal(x);
    }
    anzwer = answer;

}


void Equation::Derivative()
{

    ///Equation will call the derivative method of each term
    //Terms will be ables to calculate there own derivatives

    string dT[Terms.size()];// array of derivative terms
    string ghostMan;

    for(int i = 0; i < Terms.size(); i++)
    {
         ghostMan = Terms[i].Derivative() ;
         dT[i] = ghostMan;
    }

   //cout << endl;
    //cout << "\n\n\nDerivatives in string form" << endl;


    for(int i = 0; i < Terms.size(); i++)
    {
         //cout << "term" << dT[i] << endl;
         PrimeTerms.push_back(dT[i]);
    }
}
