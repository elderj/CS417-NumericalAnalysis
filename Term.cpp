#include "Term.h"



Term::Term(string trm)
{
    og = trm; //Save the "og" input could be useful later
    string cf = ""; //coefficienticient string
    string sv = ""; //x stuff string tbe
    string ex = "";

    /*
    CHECKING Part
    */

    ///Get Sign of term
    if( og[0] == '+' )
    {
        sign = false;
    }
    if( og[0] == '-' )
    {
        sign = true;
    }

    ///check if just a digit
    for(int i = 1; i < trm.size(); i++)
    {
            if(dig)
            {
                if(isdigit(trm[i]) || trm[i] == '.')
                {
                    ///grab coef
                    cf = cf + trm[i];
                }
                else
                {
                    if(i == 1)
                    {
                        hasCoef = false;
                    }
                    sv = trm[i];
                    dig = false;
                }
            }
            else
            {
                sv = sv + trm[i];
            }
    }

    ///check if x has exponent
    for(int i = 0; i < sv.size(); i++)
    {
        if(expn == false)
        {
            //cout << sv[i] ;
            if(sv[i] == '^')
            {
                expn = true;
            }
        }
        else
        {
            ex = ex + sv[i];
        }
    }

    if(expn == false)
    {
        if( dig == false )
        {
            xUno = true;
        }
    }


    ///check for special functions


    /*
    DONE WITH CHECKING PART
    */

    ///Finish up stuff

    xterm = sv;
    expo = ex;
    exponent = atof( expo.c_str() );
    coef = cf;
    coefficient = atof( coef.c_str() );

    //TermStats();

}

void Term::TermStats()
{
    cout << "!!!!!!!!Stats!!!!!!!"<< og << endl;

    if(dig)
    {
        cout << "1.Is a digit!"  << coefficient<< endl;
    }
    else
    {
        cout << "1.Is not a digit!" << endl;
    }

    if(sign)
    {
        cout << "2.Negative" << endl;
    }
    else
    {
        cout << "2.Positive" << endl;
    }

    if(expn)
    {
        cout << "3.Has exponent" << endl;
    }
    else
    {
        cout << "3.No Exponent" << endl;
    }

    if(xUno)
    {
        cout << "4.X is degree one" << endl;
    }
    else
    {
        cout << "4.X is not degree one" << endl;
    }

    if(hasCoef)
    {
        cout << "5.X has a coef" << endl;
    }
    else
    {
        cout << "5.X has no coef" << endl;
    }

}


double Term::xVal(double x) /// Calculate the appropriate value to return
{
    double answer = 0;

    ///Return a digit
    if(dig)
    {
        answer = coefficient;
        if (sign == true)
        {
            answer  = -answer;
        }
    }

    if(xUno)// if there is an x degree of one
    {
        if(hasCoef)
        {
            //Term is x with a coef
            answer = (coefficient * x);
        }
        else
        {
            //Term is just 'x'
            answer = x;
        }

        if (sign == true)
        {
            answer  = -answer;
        }
    }

    if(expn)
    {
        answer = pow(x, exponent);
        if(hasCoef)
        {
            answer = coefficient * answer;
        }

    }
    return answer;
}

string Term::Derivative()
{
    double newCoefficient;
    double newExponent;

    string tre;
   // cout << "d/dx(" << og << ")=" ;

    //X is a constant
    if(dig)
    {
        cout <<"0";
        tre = "+0";
    }
    //X is not a constant (has an x somewhere in the term)
    else
    {
        ///Has Coef
        if(hasCoef)
        {
            if(expn)
            {
                ///derivative of cx^w NEEDS HELP STILL
                //cout << "Has coef and exp" << endl;

                //cout << "coef" << coefficient << endl;
                //cout << "expo" << exponent << endl;

                newCoefficient =  coefficient * exponent;
                newExponent    =  exponent - 1;

                //cout << "coef(n) " << newCoefficient << endl;
                //cout << "expo(n) " << newExponent << endl;

                std::ostringstream osC;
                osC << (newCoefficient);
                std::string strC = osC.str();
                //cout << "strC" << strC << endl;

                std::ostringstream osE;
                osE << (newExponent);
                std::string strE = osE.str();
                //cout << "strE" << strE << endl;

                tre = strC;
                if(newExponent != 0)
                {
                    tre = tre + "x";
                    if(newExponent != 1)
                    {
                        tre = tre + '^' + strE;
                    }
                }

            if(newCoefficient > 0)
            {
                tre = '+' + tre;
            }

            }
            else
            {
                // derivative of cx = c GOOD
                //cout << "has no exponent has coef" << endl;
                tre = coef;
                if(sign)
                {
                    tre = '-' + tre;
                }
                else
                {
                    tre = '+' + tre;
                }
            }

        }
        ///No Coef
        else
        {
            if(expn)
            {
                double re;
                //derivative of x^n GOOD
                re = atof(expo.c_str());
                tre = expo;
                tre = tre + 'x';
                tre = tre + '^';
                std::ostringstream os;
                os << (re -1);
                std::string str = os.str();

                tre = tre + str;
            }
            else
            {
                //derivative of x GOOD
                tre = "1";
                //cout << tre;
                if(sign)
                {
                    tre = '-' + tre;
                }
                else
                {
                    tre = '+' + tre;
                }
            }
        }
    }





    //cout << endl;
    return tre;
}
