#include "LUDecomposition.h"

LUDecomposition::LUDecomposition(vector<double> & nput)
{
    ///Set rows
    cout << "\nLUDecomposition Solver" << endl;
    rows = nput[0];
    cols = nput[1];
    SetMatrices(rows, cols, nput);
    Decompose();
    PrintLU();
    Finisher();
    Output();
}

void LUDecomposition::SetMatrices(int rows, int cols, vector<double> & mtxData)
{

    vector<double> shifter;
    int aLimit = rows*cols +2 ;
    mtxSize = rows*cols;
    int r = 0;
    int c = 0;

    ///Put values into A
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


///Decompose A into L & U
void LUDecomposition::Decompose()
{
    unsigned int r = 0;
    unsigned int c = 0;
    vector<double> shifter;
    ///Set U
    for(int i =0; i < mtxSize; i++)
    {
        ///Set all zeros prevent junk values
        shifter.push_back(NULL);
        c++;
        if(c == cols)
        {
            mtxU.push_back(shifter);
            mtxL.push_back(shifter);
            shifter.clear();
            cout << endl;
            c = 0;
            r++;
        }


    }
    ///Freebies in one swoop
    for(int r = 0; r < rows; r++)
    {
        mtxL[r][r]=1;
        mtxU[0][r]=mtxA[0][r];
    }

        //PrintLU();

    r = 0;
    c = 0;
    ///Stepping and enjoying
    for(int step = 1; step < rows; step++)
    {
        //cout << "\nL:" << step << endl ;
        for(int z = step -1; z < cols-1; z++)
        {
            r = z + 1;
            c = step -1;


            double answer;
            if((step - 1) == 0)
            {
                answer = (1/mtxU[c][c]) * mtxA[r][c];

            }
            else
            {

                double temp = 0;
                answer = 1/mtxU[c][c];
                for(int i = 0; i < c; i++)
                {
                    //cout << "mtxU" << i << c << " * mtxL" << r << i  ;
                    temp = temp + (mtxU[i][c] * mtxL[r][i]);
                }

                temp = mtxA[r][c] - temp;
                answer = answer * temp;
                ///answer = 222;
            }
            mtxL[r][c] = answer;

            //cout << endl << endl;
        }

        //cout << "\nU:" << endl ;
        double answer;

        for(int z = step; z < cols; z++)
        {
            r = step;
            c = z;
            //cout << "mtxA" << r << c << " - ";
            answer = mtxA[r][c];
            double temp = 0;
            //cout << "(";
            for(int i = 0; i < step ; i++)
            {
               // cout << "+   mtxU"<< i << c<< "  +  mtxL" << r << i;
                temp = temp + (mtxU[i][c] * mtxL[r][i]);
            }
            //cout << ")" << endl;
            answer = answer - temp; ///mtxA - (sum of uic )
            mtxU[r][c] = answer;

           // cout << "\n\n";
        }

    }
}

///Solve

///Output

void LUDecomposition::PrintLU()
{
int r = 0;
int c = 0;

    cout << "L:" << endl;
    for(int i = 0; i < mtxSize; i++)
    {
    cout << mtxL[r][c] << " ";

    c++;
    if(c == cols)
    {
        cout << endl;
        c = 0;
        r++;
    }


    }
    r = 0;
    c = 0;
    cout << "\nU:" << endl;
    for(int i = 0; i < mtxSize; i++)
    {
        cout << mtxU[r][c] << " ";
        c++;
        if(c == cols)
        {
            cout << endl;
            c = 0;
            r++;
        }
    }
}

void LUDecomposition::Finisher()
{
    //vector<double> y;
    ///Ly = b
    AugmentedMatrix * lb = new AugmentedMatrix(mtxL, mtxB);

    vector<double> ans;
    ans = lb->RREF();
    delete lb;


    ///Ux = y
    AugmentedMatrix * uy = new AugmentedMatrix(mtxU, ans);
    xNew = uy->RREF();
}

void LUDecomposition::Output()
{
  cout << "\n Output file saved to 'LUDecomposition.txt'" << endl;
  ofstream myfile ("LUDecomposition.txt");
  if (myfile.is_open())
  {
    for(int i = 0; i < xNew.size(); i++)
    {
        cout << xNew[i] << endl;
        myfile << xNew[i] << " ";
    }
    myfile.close();
  }
  else cout << "Unable to open file";

}

