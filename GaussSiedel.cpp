#include "GaussSiedel.h"


GaussSiedel::GaussSiedel(vector<double> & nput)
{

    cout << "Gauss-Siedel Iterative Solver" << endl;

    ///Get rows + cols from input file
    rows = nput[0];
    cols = nput[1];

    SetMatrices(rows, cols, nput);
    SetL();  SetU();
    GetLI();
    SetT();  SetC();
    SetX();

    while (solved == false)
    {
        Solve();
    }
    Output();
}

void GaussSiedel::SetMatrices(int rows, int cols, vector<double> & mtxData)
{
    for(short unsigned int i = 0; i < rows; i++ )
    {
        xNew.push_back(0);
    }
    vector<double> shifter;
    int aLimit = rows*cols +2 ;
    mtxSize = rows*cols;
    int r = 0;
    int c = 0;


    for (int i = 2; i < aLimit; i++)
    {
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

    for (int i = aLimit; i<aLimit+rows; i++)
    {
        mtxB.push_back(mtxData[i]);
    }
}


void GaussSiedel::SetX()
{
    for(int i = 0; i < rows;  i++)
    {
        xOld.push_back(1);
    }
}

void GaussSiedel::SetL()
{
    int r = 0;
    int c = 0;
    vector<double> shifter;

    for(int i = 0; i < mtxSize; i++)
    {
        if(c <= r)
        {
            shifter.push_back(mtxA[r][c]);
            c++;
        }
        else
        {
            shifter.push_back(0);
            c++;
        }

        if (c == cols)
        {
            c=0;
            mtxL.push_back(shifter);
            shifter.clear();
            r++;
        }
    }
}

void GaussSiedel::SetU()
{
    int r = 0;
    int c = 0;
    vector<double> shifter;

    for(int i = 0; i < mtxSize; i++)
    {

        if(r <= c-1)
        {
            shifter.push_back(mtxA[r][c]);
            c++;
        }
        else
        {
            shifter.push_back(0);
            c++;
        }
        if (c == cols)
        {
            c=0;
            mtxU.push_back(shifter);
            shifter.clear();
            r++;
        }
    }
}

void GaussSiedel::GetLI()
{
    mtxLI = mtxL;
    double temp;
    if(cols!=2 && rows == 2)
    {
        double det = 0;
        det = mtxLI[0][0] * mtxLI[1][1];
        det = 1/det;

        temp = mtxLI[0][0] ;
        mtxLI[0][0] = mtxLI[1][1] * det;
        mtxLI[1][1] = temp * det;

        mtxLI[0][1] = 0;
        mtxLI[1][0] = -mtxLI[1][0] * det;
    }
    else ///When not 2x2
    {
        vector<double> shifter;
        for(int r = 0; r < rows; r ++)
        {
            for(int c = 0; c < cols; c++)
            {
                shifter.push_back(mtxL[r][c]);
            }
            for (int i = 0; i < rows; i++)
            {
                if(i==r)
                {
                    shifter.push_back(1);
                }
                else
                {
                    shifter.push_back(0);
                }
            }
            aug.push_back(shifter);
            shifter.clear();

        }

        double rbo;
        double nxt;
        for(int step = 0; step < cols; step++)
        {

                rbo = aug[step][step] ;
                for(int i = 0; i < cols*2; i++)
                {
                    aug[step][i] = aug[step][i] / rbo;
                }

                for(int r = 0; r < rows; r++)
                {
                    if(r != step)
                    {
                        nxt = aug[r][step];
                        for (int c = 0; c < cols*2; c++)
                        {
                            aug[r][c] = aug[r][c] + -nxt*aug[step][c];
                        }
                    }
                }
        }
            int r = 0;
            int c = 0;
            for(int i = 0; i < mtxSize; i++)
            {
                mtxLI[r][c] = aug[r][c+cols] ;
                c++;
                if (c == cols)
                {
                    c = 0;
                    r++;
                }
            }
        }
}

void GaussSiedel::SetT()
{
    int r = 0;
    int agr = 0;
    double temp;
    int c = 0;
    double tempSum = 0 ;
    vector<double> shifter;
    for(int rowstep = 0; rowstep < rows; rowstep++)
    {
        agr = 0;

            for(int i = 0; i < mtxSize; i++)
            {
                temp = -mtxLI[r+rowstep][c]*mtxU[c][r+agr];
                tempSum = tempSum + temp;

                c++;

                if(c == cols)
                {
                    shifter.push_back(tempSum);
                    agr++;
                    tempSum = 0;
                    c = 0;
                }

            }
        mtxT.push_back(shifter);
        shifter.clear();
    }
}
void GaussSiedel::SetC()
{
    int r =0;
    int c = 0;
    double shifter;
    double temp;
    for(int i = 0; i < mtxSize; i++)
    {
        temp = mtxLI[r][c] * mtxB[c];
        shifter = temp + shifter;
        c++;
        if (c == cols)
        {
            mtxC.push_back(shifter);
            shifter = 0;
            c = 0;
            r++;
        }


    }

}




void GaussSiedel::Solve()
{
    vector<double> tempRow;
    int r = 0;
    int c = 0;
    double temp = 0;
    double tempSum = 0;
    vector<double> shifter;
    for(int i = 0; i < mtxSize; i++)
    {
        temp = mtxT[r][c]*xOld[c] ;
        tempSum = tempSum + temp;
        c++;
        if(c == cols)
        {
            tempRow.push_back(tempSum);
            tempSum = 0;
            cout << endl;
            c = 0;
            r++;
        }
    }
    iterations++;
    cout << "iterations:" << iterations << endl;
    cout << "xNew:" << endl;
    for(int i = 0; i < tempRow.size(); i++)
    {
        xNew[i] = tempRow[i] + mtxC[i];
        cout << xNew[i] << endl ;
    }
    cout << endl;

    temp = 0;
    tempSum = 0;
    tempRow.clear();

    for(int i = 0; i < xNew.size(); i++)
    {
        temp = xOld[i] - xNew[i];
        temp = fabs(temp);
        tempSum = tempSum + temp;

    }


    if(tempSum < TOLERABLEERROR)
    {
        solved = true;
    }
    else
    {
        for(int i = 0; i < rows; i++)
        {
        xOld[i] = xNew[i];
        }
    }


}

void GaussSiedel::Output()
{

  cout << "\n Output file saved to 'GaussSiedel.txt'" << endl;

  ofstream myfile ("GaussSiedel.txt");
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


