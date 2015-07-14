#include "Jacobi.h"
#include "GaussianElimination.h"

Jacobi::Jacobi(vector<double> & nput)
{
    ///Set rows
    cout << "\nJacobi Iterative Solver" << endl;
    rows = nput[0];
    cols = nput[1];
    SetMatrices(rows, cols, nput);


    SetDI();
    SetU();
    SetL();

    SetT();
    SetC();
    SetX();
    while(solved == false)
    {
        Solve();
    }
    Output();
}



void Jacobi::SetMatrices(int rows, int cols, vector<double> & mtxData)
{

    vector<double> shifter;
    int aLimit = rows*cols +2 ;
    mtxSize = rows*cols;
    int r = 0;
    int c = 0;


    ///Put values into A
    //cout << "A:" << endl;
    for (int i = 2; i < aLimit; i++)
    {

        //cout << mtxData[i] << "             " << r << c << "\n" ;
        shifter.push_back(mtxData[i]);
        c++;
        if (c == cols)
        {
        c = 0;
        mtxA.push_back(shifter);
        shifter.clear();
        r++;
        }

    }
    ///Put Values into b
    //cout << "\nB:" << endl;
    for (int i = aLimit; i<aLimit+rows; i++)
    {
        //cout << mtxData[i] << endl;
        mtxB.push_back(mtxData[i]);
    }
}


void Jacobi::SetDI()
{
    unsigned short int r = 0;
    unsigned short int c = 0;
    vector<double> shifter;
    for(int i = 0; i < mtxSize; i++)
    {



        if(c == r)
        {
            //cout << 1/mtxA[r][c] << " ";
            shifter.push_back(1/mtxA[r][c]);
        }
        else
        {
            //cout << "0 ";
            shifter.push_back(0);
        }
        c++;
        if(c == cols)
        {
            mtxDI.push_back(shifter);
            shifter.clear();
            //cout << endl;
            c=0;
            r++;
        }

    }
}


void Jacobi::SetU()
{
    mtxU = mtxA;
    unsigned short r = 0;
    unsigned short c = 0;
    vector<double> shifter;
    for(int i = 0; i < mtxSize; i++)
    {
        if(c <= r)
        {
            //cout << "0 ";
            mtxU[r][c] = 0;
        }
        else
        {
            //cout << mtxA[r][c] << " ";
            mtxU[r][c] = mtxA[r][c];
        }
        c++;
        if(c == cols)
        {
            mtxU.push_back(shifter);
            shifter.clear();
            //cout << endl;
            c = 0;
            r++;
        }
    }
}

void Jacobi::SetL()
{
    mtxL = mtxA;
    unsigned short r = 0;
    unsigned short c = 0;
    vector<double> shifter;
    for(int i = 0; i < mtxSize; i++)
    {
        if(c >= r)
        {
            //cout << "0 ";
            mtxL[r][c] = 0;
        }
        else
        {
            //cout << mtxA[r][c] << " ";
            mtxL[r][c] = mtxA[r][c];
        }
        c++;
        if(c == cols)
        {
            mtxL.push_back(shifter);
            shifter.clear();
            //cout << endl;
            c = 0;
            r++;
        }
    }
}

void Jacobi::SetT()
{
    mtxT = mtxA;
    unsigned short int r = 0;
    unsigned short int c = 0;
    double temp = 0;
    for(int i = 0; i < mtxSize; i++)
    {
        temp = -mtxU[r][c];
        temp =  temp - mtxL[r][c];
        mtxT[r][c] = temp;



        c++;
        if(c == cols)
        {
            c=0;
            r++;
        }
    }

    r = 0;
    c = 0;
    temp = 0;
    double tempSum = 0;
    int helper = 0;
    for(int rowStep = 0; rowStep < rows; rowStep++)
    {
        for (int step = 0; step < rows*2; step++)
        {
            temp = mtxDI[rowStep][c] * mtxT[c][helper] ;
            tempSum = tempSum + temp;
            c++;
            if(c == cols)
            {
                helper++;
                mtxT[rowStep][step/2] = tempSum;
                tempSum = 0;
                c = 0 ;
            }

        }
        helper = 0;
    }

    r = 0; c = 0;
    for(int i = 0; i < mtxSize; i++)
    {
        c++;
        if(c == cols)
        {
            c=0;
            r++;
        }
    }
    cout << endl;
}

void Jacobi::SetC()
{
    unsigned short int r = 0;
    unsigned short int c = 0;
    double temp = 0;
    double tempSum = 0;

    for(int i = 0; i < mtxSize; i++)
    {
        temp = mtxDI[r][c] * mtxB[c] ;
        tempSum = temp + tempSum;
        c++;
        if(c == cols)
        {
            mtxC.push_back(tempSum);
            c=0;
            tempSum=0;
            r++;
        }
    }
}



void Jacobi::SetX()
{

    for(int i = 0; i < rows;  i++)
    {
        xOld.push_back(1);
    }

}

void Jacobi::Solve()
{
    unsigned short int r = 0;
    unsigned short int c = 0;
    double temp = 0;
    double tempSum = 0;

    for(int i = 0; i < mtxSize; i++)
    {
        temp = mtxT[r][c] * xOld[c];
        tempSum = temp + tempSum;

        c++;
        if(c == cols)
        {
            xNew.push_back(tempSum);
            tempSum = 0;
            c = 0;
            r++;
        }
    }
    r = 0; c = 0;
    for (int i = 0; i < rows; i++)
    {
        xNew[i] = xNew[i] + mtxC[i];
    }

    tempSum = 0;
    iterations++;
    cout << "iterations:" << iterations << endl;

    for(int i = 0; i < xNew.size(); i++)
    {
        cout << xNew[i] << endl ;
    }
    cout << endl;
    tempSum = 0;
    for(int i = 0; i < xNew.size(); i++)
    {
        temp = xOld[i] - xNew[i];
        temp = fabs(temp*temp);
        tempSum = tempSum + temp;
    }

    if(sqrt(tempSum) < TOLERABLEERROR)
    {
       solved = true;
    }


    for(int i = 0; i < xNew.size(); i++)
    {
        xOld[i] = xNew[i];
    }
    xNew.clear();
}

void Jacobi::Output()
{
  cout << "\n Output file saved to 'Jacobi.txt'" << endl;
  ofstream myfile ("Jacobi.txt");
  if (myfile.is_open())
  {
    for(int i = 0; i < xOld.size(); i++)
    {
        myfile << xOld[i] << " ";
    }
    myfile.close();
  }
  else cout << "Unable to open file";

}

