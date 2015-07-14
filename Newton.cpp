#include "Newton.h"


Newton::Newton()
{
    double xZero;
    cout << "\nEnter an equation:";
    cin >> inputEQ;
    inputEQ = "3x^2-2x";
    cout << "\nInitial Guess:";
    cin >> xZero;

    xZero = 10;
    Solve(xZero);
}

void Newton::Solve(double xZ)
{
    //cout << "\n Solving:" << inputEQ << " x0:" << xZ << endl;
    vector<string> TermInitiators;
    string temp;

    for(int i = 0; i < inputEQ.size(); i++)
    {
        ///Check for sign of leading term
        if(i == 0)
        {
            if(inputEQ[i]=='-')
            {
                //First term was negative
                    //cout << inputEQ[i] << "<- 1 was neg" << endl;
                    temp = temp + inputEQ[i];
                }
                else
                {
                    //First term was positive
                    //cout << inputEQ[i] << "<- 1 was pos" << endl;
                    temp = temp + '+';
                    temp = temp + inputEQ[i];
                }
        }
        else
        {

            if( inputEQ[i] == '+' || inputEQ[i] == '-' )
            {
                if(inputEQ[i-1] == '^' && inputEQ[i] == '-')
                {
                    temp = temp + inputEQ[i];
                }
                else
                {
                    //End of term
                    TermInitiators.push_back(temp);
                    temp = "";
                    temp = temp + inputEQ[i];
                }
            }
            else
            {
                    //Term component
                    temp = temp + inputEQ[i];
                }
            }
        }
        //final push
        TermInitiators.push_back(temp);


        ///Now that we have terms in a vector of strings
        ///Pass that vector to the constructor of an
        ///Equation.


        double xIn = xZ;
        double xOut;
        double fX, fXPrime;//Results

        Equation * theEquation = new Equation(TermInitiators); ///creates an equation which can accept values



        ///Get derivative of equation
        theEquation->Derivative();

        vector<string> pTermsInitiators;

        for(int i = 0; i < theEquation->PrimeTerms.size(); i++)
        {
            pTermsInitiators.push_back(theEquation->PrimeTerms[i].og);
        }


        Equation * thePrimeEquation = new Equation(pTermsInitiators); ///creates an equation of prime terms which can accept values


        /*                                    x

        ------==Iterative Solving Part==------

        x                                     */

        double a = 0,b = 0;
        double test = 0;

        xIn = 1;
        int j = 0;
        while(solved == false)
        {

            theEquation->plugin(xIn);
            a = theEquation->anzwer;

            thePrimeEquation->plugin(xIn);
            b = thePrimeEquation->anzwer;

            xOut = a / b;
            xOut = xIn - xOut;
            xIn = xOut;

            ///Test if close enough
            theEquation->plugin(xIn);
            test = theEquation->anzwer;
            if(test < TOLERABLEERROR)
            {
                //cout << "!!Decent!!" << endl;
                solved = true;
            }

            j++;
        }

        cout << "\n\nAnswer is: "<< xOut << " after " << j << " iterations." << endl;


}
