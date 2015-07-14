#include "Bisection.h"

Bisection::Bisection()
{


    cout << "\nEnter an equation:";
    cin >> inputEQ;

    cout << "\nRange top:" ;
    cin >> A;

    cout << "\nRange low:" ;
    cin >> B;

    Solve();
}

void Bisection::Solve()
{

    vector<string> tSto;
    string temp;

    ///Parse through Equation string to get individual term strings
    //A string representing a term to be added or subtracted is
    //used to construct new terms.
        for(int i = 0; i < inputEQ.size(); i++)
        {
            ///Check for sign of leading term
            if(i == 0)
            {
                if(inputEQ[i]=='-')
                {
                    //First term was negative

                    temp = temp + inputEQ[i];
                }
                else
                {
                    //First term was positive

                    temp = temp + '+';
                    temp = temp + inputEQ[i];
                }
            }
            else
            {
                if( inputEQ[i] == '+' || inputEQ[i] == '-' )
                {
                    //End of term
                    tSto.push_back(temp);
                    temp = "";
                    temp = temp + inputEQ[i];
                }
                else
                {
                    //Term component
                    temp = temp + inputEQ[i];
                }
            }
        }
        //final push
        tSto.push_back(temp);

        Equation * theEquation = new Equation(tSto); ///creates an equation which can accept values

        //plug in initial values
        double fA, fB, fC;
        bool signA, signB, signC;

        while(solved == false && er == false)
        {

            cout << "\niteration:"<< iterations<< endl;

            theEquation->plugin(A);
            fA = theEquation->anzwer;
            cout << "f(A)" << fA  << endl;

            if(fA == 0)
            {
                cout << "Root at A=" << A << "  f(A)=0  Done." << endl;
                solved = true;
                finalC = A;
            }
            else
            {
                // check sign
                if(fA > 0)
                {
                   signA = false;
                }
                else
                {
                   signA = true;
                }
            }

                theEquation->plugin(B);
                fB = theEquation->anzwer;
                cout << "f(B)" << fB  << endl;

                if(fB == 0)
                {
                    cout << "Root at B=" << B << "  f(B)=0  Done." << endl;
                    solved = true;
                    finalC = B;
                }
                else
                {
                                // check sign
                    if(fB > 0)
                    {
                       signB = false;
                    }
                    else
                    {
                       signB = true;
                    }

                }

                if((signA == false && signB == true)||(signA == true && signB == false))
                {

                    C = (A + B)/2;
                    cout << "c:" << C << endl;

                    theEquation->plugin(C);
                    fC = theEquation->anzwer;
                    cout << "f(C)" << fC  << endl;

                    //check if another loop is necessary.
                    if(fabs(fC) < TOLERABLEERROR)
                    {
                        solved = true;// final condition
                        finalC = C;
                    }
                    else
                    {
                        //check which should be set to c
                        if(fC > 0)
                        {
                            cout << "c was pos" << endl;
                            if(signA == false)
                            {
                                A = C;
                            }
                            else
                            {
                                B = C;
                            }
                        }
                        else
                        {
                            cout << "c was neg" << endl;
                            if(signA == true)
                            {
                                A = C;
                            }
                            else
                            {
                                B = C;
                            }
                        }

                    }
                    iterations++;
                }
                else
                {
                    er = true;
                }

            }

                if(er == true)
                {
                    cout << "root error" << endl;
                }
                else
                {
                cout << "\n\nAnswer is: "<< finalC  << " after " << iterations << " iterations." << endl;
                }

            delete theEquation;
}

