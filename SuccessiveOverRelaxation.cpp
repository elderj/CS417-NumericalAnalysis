#include "SuccessiveOverRelaxation.h"


SuccessiveOverRelaxation::SuccessiveOverRelaxation(vector<double> & nput)
{

    cout << "Gauss-Siedel Iterative Solver" << endl;

    ///Get rows + cols from input file
    rows = nput[0];
    cols = nput[1];

    SetMatrices(rows, cols, nput);
    SetL();   SetU();
    GetLI();
    SetT();   SetC();
    SetX();

    while (solved == false)
    {
        Solve();
    }
    Output();
}

void SuccessiveOverRelaxation::SetMatrices(int rows, int cols, vector<double> & mtxData)
{
    for(short unsigned int i = 0; i < rows; i++ )
    {
        xNew.push_back(0);
        xOmega.push_back(0);
    }
    vector<double> shifter;
    int aLimit = rows*cols +2 ;
    mtxSize = rows*cols;
    int r = 0;
    int c = 0;


    ///Put values into A
    //cout << "A:" << endl;
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
    ///Put Values into b
    for (int i = aLimit; i<aLimit+rows; i++)
    {
        mtxB.push_back(mtxData[i]);
    }




}




void SuccessiveOverRelaxation::SetX()
{


    ///Get initial guess the size of the number of rows

    for(int i = 0; i < rows;  i++)
    {
        //cout  <<"xOld[" << i << "]--->";
        //cin >> a;

        xOld.push_back(1);
    }
        //cout << "\n" << "Guess Recieved." << endl;



}

void SuccessiveOverRelaxation::SetL()
{
    //cout << "\nL:" << endl;
    int r = 0;
    int c = 0;
    vector<double> shifter;

    for(int i = 0; i < mtxSize; i++)
    {
        if(c <= r)
        {
            //cout << mtxA[r][c] << " ";
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
            //cout << endl;
            c=0;
            mtxL.push_back(shifter);
            shifter.clear();
            r++;
        }
    }
}

void SuccessiveOverRelaxation::SetU()
{
    //cout << "\nU:" << endl;
    int r = 0;
    int c = 0;
    vector<double> shifter;

    for(int i = 0; i < mtxSize; i++)
    {

        if(r <= c-1)
        {
            //cout << mtxA[r][c] << " ";
            shifter.push_back(mtxA[r][c]);
            c++;
        }
        else
        {
            //cout << "0 ";
            shifter.push_back(0);
            c++;
        }
        if (c == cols)
        {
            //cout << endl;
            c=0;
            mtxU.push_back(shifter);
            shifter.clear();
            r++;
        }
    }
}

void SuccessiveOverRelaxation::GetLI()
{
    mtxLI = mtxL;
    double temp;
    ///For the two by two case probably faster
    if(cols == 2 && rows == 2)
    {
        double det = 0;
        det = mtxLI[0][0] * mtxLI[1][1];
        det = 1/det;


        ///ad
        temp = mtxLI[0][0] ;
        mtxLI[0][0] = mtxLI[1][1] * det;
        mtxLI[1][1] = temp * det;

        ///bc
        mtxLI[0][1] = 0;
        mtxLI[1][0] = -mtxLI[1][0] * det;
    }
    else ///When not 2x2
    {
        //cout << "\nbeer me beer me" ; // or set up the augmented matrix to be solved
        vector<double> shifter;
        for(int r = 0; r < rows; r ++)
        {
            for(int c = 0; c < cols; c++)
            {
                //cout << mtxL[r][c] << " ";
                shifter.push_back(mtxL[r][c]);
            }
            for (int i = 0; i < rows; i++)
            {
                if(i==r)
                {
                    //cout << "1 " ;
                    shifter.push_back(1);
                }
                else
                {
                    //cout << "0 ";
                    shifter.push_back(0);
                }
            }
            aug.push_back(shifter);
            shifter.clear();

        }
        //cout << "aug is set";
        //printAug();



        double holydiver;
        double dio;
        for(int step = 0; step < cols; step++)
        {

            //cout << "step:" << step + 1 << endl;


                holydiver = aug[step][step] ;
                ///Part A:
                for(int i = 0; i < cols*2; i++)
                {
                    aug[step][i] = aug[step][i] / holydiver;
                }

                ///Part B:
                for(int r = 0; r < rows; r++)
                {
                    if(r != step)
                    {
                        //cout << "Row other than focus" << endl;
                        dio = aug[r][step];
                        for (int c = 0; c < cols*2; c++)
                        {
                            //cout << aug[r][c] << " + (" << -dio << "*" << aug[step][c] << ")" <<  endl;
                            aug[r][c] = aug[r][c] + -dio*aug[step][c];
                        }
                    }
                }


        }
            int r = 0;
            int c = 0;
            for(int i = 0; i < mtxSize; i++)
            {
                mtxLI[r][c] = aug[r][c+cols] ;
                //cout << mtxLI[r][c] << endl;

                c++;
                if (c == cols)
                {
                    c = 0;
                    r++;
                }
            }
        }

}



void SuccessiveOverRelaxation::SetT()
{
    //cout << "T = -DI*U" << endl;
    int r = 0;
    int pooper = 0;
    double temp;
    int c = 0;
    double tempSum = 0 ;
    vector<double> shifter;
    for(int rowstep = 0; rowstep < rows; rowstep++)
    {
        pooper = 0;

            for(int i = 0; i < mtxSize; i++)
            {
                temp = -mtxLI[r+rowstep][c]*mtxU[c][r+pooper];
               // cout << -mtxLI[r+rowstep][c] << "*" << mtxU[c][r+pooper] << " = " << temp << endl;
                tempSum = tempSum + temp;

                c++;

                if(c == cols)
                {
                    //cout << "time to add "<< tempSum << endl;

                    shifter.push_back(tempSum);
                    pooper++;
                    tempSum = 0;
                    c = 0;
                }

            }


        //cout << "time to clear;" << endl;
        mtxT.push_back(shifter);
        shifter.clear();
    }

   //cout << mtxT[0][0] << " " << mtxT[0][1] << endl;

   // cout << mtxT[1][0] << " " << mtxT[1][1] << endl;
}
void SuccessiveOverRelaxation::SetC()
{
    //cout << "C = DI*b" << endl;
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
            for(r = 0; r < cols; r++)
        {
            //cout << mtxC[r] << endl;
        }
}

void SuccessiveOverRelaxation::printAug()
{
    int r = 0;
    int c = 0;
    cout << "\n";
    for(int i = 0; i < mtxSize*2; i ++)
    {

        cout << aug[r][c] << " " ;
        c++;
        if(c == rows * 2)
        {
            cout << endl;
            c = 0;
            r++;
        }

    }

}


void SuccessiveOverRelaxation::Solve()
{
    vector<double> tempRow;
   // cout << "\n" << " Solving. "<< endl;


    //cout << "TxX+C" << endl;
    int r = 0;
    int c = 0;
    double temp = 0;
    double tempSum = 0;
    vector<double> shifter;
    for(int i = 0; i < mtxSize; i++)
    {
        temp = mtxT[r][c]*xOld[c] ;
        //cout << mtxT[r][c] << " * " << xOld[c] << " = " << temp << endl;
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
        xOmega[i] = (1-omega) * xOld[i] + omega * xNew[i];
        //cout << xNew[i] << endl ;
        cout << xOmega[i] << endl ;
    }
    cout << endl;

    temp = 0;
    tempSum = 0;
    tempRow.clear();

    ///Error Checking Part:
    //Current Iteration Error
    for(int i = 0; i < xOmega.size(); i++)
    {
        temp = xOmega[i] - xOld[i];
        temp = fabs(temp);
        //cout << temp;
        tempSum = tempSum + temp;

    }


    if(tempSum < TOLERABLEERROR)
    {
        solved = true;
    }
    else
    {
        //tempRow.clear()
        for(int i = 0; i < rows; i++)
        {
        xOld[i] = xOmega[i];
        }
    }


}

void SuccessiveOverRelaxation::Output()
{

  cout << "\n Output file saved to 'SuccessiveOverRelaxation.txt'" << endl;

  ofstream myfile ("SuccessiveOverRelaxation.txt");
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


