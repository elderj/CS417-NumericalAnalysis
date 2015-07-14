#include "Regula.h"


Regula::Regula()
{
    cout << "\nEnter an equation:";
    cin >> inputEQ;

    cout << "\nRange top:" ;
    cin >> A;

    cout << "\nRange low:" ;
    cin >> B;

    Solve();
}


void Regula::Solve()
{
    // cout << "\nProcessing:" << inputEQ << endl;
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

        double fA, fB, fC;
        double num, den, frac;

        Equation * theEquation = new Equation(tSto); ///creates an equation which can accept values

        while(solved == false)
        {
            theEquation->plugin(A);
            fA = theEquation->anzwer;

            theEquation->plugin(B);
            fB = theEquation->anzwer;

            num = (B - A)*fA;
            den = fB - fA;

            C = A - (num/den);

            theEquation->plugin(C);
            fC = theEquation->anzwer;

            cout << iterations << ":  " << C << "      " << fC << endl;

            if(fabs(fC) < TOLERABLEERROR)
            {
                cout << "\n\nAnswer is: "<< C  << " after " << iterations << " iterations." << endl;
                solved = true;
            }
            else
            {
                if(C > 0)
                {
                    ///C was positive
                    if(A > 0)
                    {
                        ///A was positve B was negative
                        A = C;

                    }
                    else
                    {
                        ///B was positive A was negative
                        B = C;
                    }

                }
                else
                {
                    ///C was negative
                    if(A > 0)
                    {
                        ///A was positve B was negative
                        B = C;

                    }
                    else
                    {
                        ///B was positive A was negative
                        A = C;
                    }

                }

            }


            iterations++;

        }





}
