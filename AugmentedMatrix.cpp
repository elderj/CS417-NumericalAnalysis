#include "AugmentedMatrix.h"

AugmentedMatrix::AugmentedMatrix(vector <vector<double> > & mtxA, vector<double> & mtxB)
{
    ///Set values from A and b in Gaussian Elimination

    aRows = mtxB.size();
    aCols = aRows + 1;
    vector<double> shifter;


    for(int r = 0; r < aRows; r++)
    {

        for(int c = 0; c < aCols; c++)
        {
            if(c < aRows)
            {
                shifter.push_back(mtxA[r][c]);
            }
            else
            {
                shifter.push_back(mtxB[r]);
                value.push_back(shifter);
                shifter.clear();
            }
        }

    }
    cout << "\n\n" ;
}

vector<double> AugmentedMatrix::RREF()
{

    vector<double> shifter;
    double grande = -1;
    short int ph = -1;
    double temp = -1;


    cout << "Start:" << endl;
    Print();

    for(int rowStep = 0; rowStep < aRows; rowStep++)
    {


        ///make the largest the top
        for(int r = 0; r < aRows; r++)
        {
            if(r>=rowStep)
            {
                if(fabs(value[r][rowStep]) > grande)
                {
                        grande = value[r][rowStep] ;
                        ph = r;
                }
            }
        }
        if(ph != rowStep)
        {
            for(int c = 0; c < aCols; c++)
            {
                temp = value[ph][c] / grande;
                shifter.push_back(temp);
                value[ph][c] = value[rowStep][c];
                value[rowStep][c] = shifter[c];
            }
            shifter.clear();
        }
        else
        {
            for(int c = 0; c < aCols; c++)
            {
                value[ph][c] = value[ph][c] / grande;
            }
        }

        ///get all 0's in row step column to go on to next step
        for(int r = 0; r < aRows; r++)
        {
            if(r != rowStep)
            {
                temp = value[r][rowStep];
                for(int c = 0; c < aCols; c++)
                {
                     value[r][c] = -temp * value[rowStep][c] + value[r][c];
                }


            }
        }

        grande = -1;
    }

    cout << "Finish:" << endl;
    Print();

    vector<double> result;
    for(int i = 0; i < aRows; i++)
    {
        result.push_back(value[i][aRows]);
    }
    return result;
}


void AugmentedMatrix::Print()
{
    for(int r = 0; r < aRows; r++)
    {
        for(int c = 0; c < aCols; c++)
        {
            cout << value[r][c] << " ";
        }
        cout << "\n\n" ;
    }
}

